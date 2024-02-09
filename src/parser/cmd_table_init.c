/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_table_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:56:38 by mottjes           #+#    #+#             */
/*   Updated: 2024/02/09 12:56:39 by mottjes          ###   ########.fr       */
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
	shell->cmd_list = first_cmd;
	count--;
	while (count)
	{
		next_cmd = malloc(sizeof(t_cmd));
		if (!next_cmd)
			malloc_fail(shell);
		next_cmd->builtin = 0;
		first_cmd->next = next_cmd;
		first_cmd = next_cmd;
		count--;
	}
	first_cmd->next = NULL;
}

void	get_redirections(t_data *shell)
{
	t_token	*token;

	token = shell->token_list;
	shell->in_file = NULL;
	shell->out_file = NULL;
	while (token)
	{
		if (token->type == RE_IN)
		{
			if (shell->in_file)
				free(shell->in_file);
			shell->in_file = ft_strdup(token->next->str);
			if (!shell->in_file)
				malloc_fail(shell);
		}
		if (token->type == RE_OUT)
		{
			if (shell->out_file)
				free(shell->out_file);
			shell->out_file = ft_strdup(token->next->str);
			if (!shell->out_file)
				malloc_fail(shell);
		}
		if (token->type == RE_APP)
		{
			if (shell->out_file)
				free(shell->out_file);
			shell->out_file = ft_strdup(token->next->str);
			if (!shell->out_file)
				malloc_fail(shell);
		}
		if (token->type == HERE_DOC)
		{
			if (shell->in_file)
				free(shell->in_file);
			shell->in_file = ft_strdup(token->next->str);
			if (!shell->in_file)
				malloc_fail(shell);
		}
		token = token->next;
	}
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
			cmds->cmd = ft_strdup(token->str);
			if (!cmds->cmd)
				malloc_fail(shell);
			//token = token->next;
			cmds->args = malloc(sizeof(char *) * (arg_count(token) + 1));
			if (!cmds->args)
				malloc_fail(shell);
			while (token && token->type == WORD)
			{
				cmds->args[i] = ft_strdup(token->str);
				token = token->next;
				i++;
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
