/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_table_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:56:38 by mottjes           #+#    #+#             */
/*   Updated: 2024/03/13 15:03:44 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cmd_list_init(t_data *shell, int count)
{
	t_cmd	*first_cmd;
	t_cmd	*next_cmd;

	first_cmd = malloc(sizeof(t_cmd));
	if (!first_cmd)
		malloc_fail(shell);
	first_cmd->builtin = 0;
	first_cmd->path = NULL;
	first_cmd->in_file = NULL;
	first_cmd->out_file = NULL;
	shell->cmd_list = first_cmd;
	count--;
	while (count)
	{
		next_cmd = malloc(sizeof(t_cmd));
		if (!next_cmd)
			malloc_fail(shell);
		next_cmd->builtin = 0;
		next_cmd->path = NULL;
		next_cmd->in_file = NULL;
		next_cmd->out_file = NULL;
		first_cmd->next = next_cmd;
		first_cmd = next_cmd;
		count--;
	}
	first_cmd->next = NULL;
}

void	get_redirections(t_data *shell)
{
	t_token	*token;
	t_cmd	*cmd;

	cmd = shell->cmd_list;
	token = shell->token_list;
	while (token)
	{
		if (token->type == PIPE)
			cmd = cmd->next;
		if (token->type == RE_IN)
		{
			if (cmd->in_file)
				free(cmd->in_file);
			cmd->in_file = ft_strdup(token->next->str);
			if (!cmd->in_file)
				malloc_fail(shell);
			check_rights(shell, cmd);
		}
		else if (token->type == RE_OUT || token->type == RE_APP)
		{
			if (cmd->out_file)
				free(cmd->out_file);
			cmd->out_file = ft_strdup(token->next->str);
			if (!cmd->out_file)
				malloc_fail(shell);
			check_rights(shell, cmd);
		}
		token = token->next;
	}
}

void	malloc_for_args(t_data *shell, t_cmd *cmds, t_token *token)
{
	cmds->cmd = ft_strdup(token->str);
	if (!cmds->cmd)
		malloc_fail(shell);
	cmds->args = malloc(sizeof(char *) * (arg_count(token) + 1));
	if (!cmds->args)
		malloc_fail(shell);
}

void	cmds_str_copy(t_token *token, t_cmd *cmds, t_data *shell)
{
	t_token	*prev;
	int		i;

	i = 0;
	prev = token;
	while (token)
	{
		if (token->type == WORD && (prev->type == WORD || prev->type == PIPE))
		{
			malloc_for_args(shell, cmds, token);
			while (token && token->type == WORD)
			{
				cmds->args[i++] = ft_strdup(token->str);
				token = token->next;
				while (token && (token->type == RE_IN || token->type == RE_OUT || token->type == RE_APP || token->type == HERE_DOC))
				{
					token = token->next;
					token = token->next;
				}
			}
			cmds->args[i] = NULL;
			cmds = cmds->next;
			i = 0;
		}
		if (token)
		{
			prev = token;
			token = token->next;
		}
	}
}

void	cmd_table_init(t_data *shell)
{
	int	count;

	count = cmds_count(shell->token_list);
	cmd_list_init(shell, count);
	cmds_str_copy(shell->token_list, shell->cmd_list, shell);
	get_redirections(shell);
}
