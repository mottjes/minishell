/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_table.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 21:12:06 by mottjes           #+#    #+#             */
/*   Updated: 2024/03/20 14:28:31 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	malloc_for_cmds(t_data *shell, t_token *token, t_cmd *cmd)
{
	cmd->cmd = ft_strdup(token->str);
	if (!cmd->cmd)
		malloc_fail(shell);
	cmd->args = safe_malloc(sizeof(char *) * (arg_count(token) + 1), shell);
	return (0);
}

static void	update_prev_token(t_token **t_ptr, t_token **prev, t_token *t)
{
	if (t)
	{
		*prev = *t_ptr;
		*t_ptr = t->next;
	}
}

void	cmds_str_copy(t_data *shell, t_token *token, t_cmd *cmd)
{
	t_token	*prev;
	int		i;

	prev = token;
	while (token)
	{
		if (token->type == WORD && (prev->type == WORD || prev->type == PIPE))
		{
			i = malloc_for_cmds(shell, token, cmd);
			while (token && token->type == WORD)
			{
				cmd->args[i++] = ft_strdup(token->str);
				token = token->next;
				while (token && (token->type == RE_IN || token->type == RE_OUT
						|| token->type == RE_APP || token->type == HERE_DOC))
				{
					token = token->next;
					token = token->next;
				}
			}
			cmd->args[i] = NULL;
			cmd = cmd->next;
		}
		update_prev_token(&token, &prev, token);
	}
}

//  use memset to init
void	cmd_list_init(t_data *shell, int count)
{
	t_cmd	*first_cmd;
	t_cmd	*next_cmd;

	first_cmd = safe_malloc(sizeof(t_cmd), shell);
	first_cmd->builtin = false;
	first_cmd->fd_in = 0;
	first_cmd->path = NULL;
	first_cmd->in_file = NULL;
	first_cmd->out_file = NULL;
	shell->cmd_lst = first_cmd;
	count--;
	while (count)
	{
		next_cmd = safe_malloc(sizeof(t_cmd), shell);
		next_cmd->builtin = false;
		next_cmd->fd_in = 0;
		next_cmd->path = NULL;
		next_cmd->in_file = NULL;
		next_cmd->out_file = NULL;
		first_cmd->next = next_cmd;
		first_cmd = next_cmd;
		count--;
	}
	first_cmd->next = NULL;
}

void	init_cmd_table(t_data *shell)
{
	int	count;

	count = cmds_count(shell->token_lst);
	cmd_list_init(shell, count);
	cmds_str_copy(shell, shell->token_lst, shell->cmd_lst);
	capture_heredoc(shell, shell->token_lst, shell->cmd_lst);
	get_redirections(shell, shell->token_lst);
}
