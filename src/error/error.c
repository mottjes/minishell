/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 14:09:37 by mottjes           #+#    #+#             */
/*   Updated: 2024/02/09 11:13:12 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_all(t_data *shell)
{
	t_token	*next_token;
	t_cmd	*next_cmd;
	int		i;
	
	i = 0;
	if (shell->input)
		free(shell->input);
	if (shell->token_list)
	{
		while (shell->token_list)
		{
			if (shell->token_list->str)
				free(shell->token_list->str);
			next_token = shell->token_list->next;
			free(shell->token_list);
			shell->token_list = next_token;
		}
	}
	if (shell->cmd_list)
	{
		while (shell->cmd_list)
		{
			if (shell->cmd_list->cmd)
				free(shell->cmd_list->cmd);
			if (shell->cmd_list->path)
				free(shell->cmd_list->path);
			while (shell->cmd_list->args[i])
			{
				free(shell->cmd_list->args[i]);
				i++;
			}
			next_cmd = shell->cmd_list->next;
			free(shell->cmd_list);
			shell->cmd_list = next_cmd;
		}
	}
	if (shell->in_file)
		free(shell->in_file);
	if (shell->out_file)
		free(shell->out_file);
	shell->restart = 0;
	shell->error = 0;
}


void	error_check(t_data *shell)
{
	if (shell->error)
	{
		shell->restart = 1;
		if (shell->error == quotes_not_closed)
			ft_putstr_fd("minishell: quotes not closed\n", 2);
		if (shell->error == command_not_found)
			ft_putstr_fd("minishell: command not found\n", 2);
		if (shell->error == syntax_error)
			ft_putstr_fd("minishell: syntax error\n", 2);
	}
}

void	malloc_fail(t_data *shell)
{
	ft_putstr_fd("minishell: malloc failed\n", 2);
	free_all(shell);
	exit(1);
}
