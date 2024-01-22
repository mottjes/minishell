/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:53:35 by mottjes           #+#    #+#             */
/*   Updated: 2024/01/22 18:05:12 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cmds_count(t_token *token)
{
	int count;

	count = 1;
	while (token)
	{
		if (token->type == PIPE)
			count++;
		token = token->next;
	}
	return (count);
}

int	arg_count(t_token *token)
{
	int count;

	count = 0;
	while (token && token->type == WORD)
	{
		token = token->next;
		count++;
	}
	return (count);
}

void	cmds_init(t_minishell *shell, int count)
{
	t_cmd *first_cmd;
	t_cmd *next_cmd;

	first_cmd = malloc(sizeof(t_cmd));
	if (!first_cmd)
		return ; 							// error handling
	shell->cmd_list = first_cmd;
	count--;
	while(count)
	{
		next_cmd = malloc(sizeof(t_cmd));
		if (!next_cmd)
			return ; 						// error handling
		first_cmd->next = next_cmd;
		first_cmd = next_cmd;
		count--;
	}
	first_cmd->next = NULL;
}

void	get_redirections(t_minishell *shell)
{
	t_token *token;
	
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
				return ;
		}
		if (token->type == RE_OUT)
		{
			if (shell->out_file)
				free(shell->out_file);
			shell->out_file = ft_strdup(token->next->str);
			if (!shell->out_file)
				return ;
		}
		if (token->type == RE_APP)
		{
			if (shell->out_file)
				free(shell->out_file);
			shell->out_file = ft_strdup(token->next->str);
			if (!shell->out_file)
				return ;
		}
		if (token->type == HERE_DOC)
		{
			if (shell->in_file)
				free(shell->in_file);
			shell->in_file = ft_strdup(token->next->str);
			if (!shell->in_file)
				return ;
		}
		token = token->next;
	}
}

void	command_table_init(t_minishell *shell)
{
	int count;

	if (!shell->token_list)
		return ;		
	count = cmds_count(shell->token_list);
	cmds_init(shell, count);
	get_redirections(shell);
	//cmds_str_copy(shell);
}

void	parser(t_minishell *shell)
{
	if (shell->error)
		return ;
	//syntax_check(token);
	command_table_init(shell);
}
