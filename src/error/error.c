/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 14:09:37 by mottjes           #+#    #+#             */
/*   Updated: 2024/03/13 13:35:30 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	free_cmd_list(t_data *shell)
{
	t_cmd	*next_cmd;
	int		i;

	i = 0;
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
			if (shell->cmd_list->in_file)
				free(shell->cmd_list->in_file);
			if (shell->cmd_list->out_file)
				free(shell->cmd_list->out_file);
			free(shell->cmd_list->args);
			next_cmd = shell->cmd_list->next;
			free(shell->cmd_list);
			shell->cmd_list = next_cmd;
		}
	}
}

void	free_all(t_data *shell)
{
	t_token	*next_token;

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
	free_cmd_list(shell);
}

void	free_environment(t_data *shell)
{
	int	i;

	i = 0;
	if (shell->envp)
	{
		while (shell->envp[i])
		{
			free(shell->envp[i]);
			i++;
		}
		free(shell->envp);
	}
}
