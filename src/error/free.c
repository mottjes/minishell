/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:14:21 by mottjes           #+#    #+#             */
/*   Updated: 2024/03/20 14:35:16 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	delete_cmds(t_data *shell, t_cmd *cmd)
{
	t_cmd	*cmd_lst;
	t_cmd	*cmd_lst_next;

	cmd_lst = shell->cmd_lst;
	while (cmd_lst != cmd)
	{
		cmd_lst_next = cmd_lst->next;
		free_cmd(cmd_lst);
		cmd_lst = cmd_lst_next;
	}
	cmd_lst_next = cmd_lst->next;
	free_cmd(cmd_lst);
	shell->cmd_lst = cmd_lst_next;
}

void	free_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->cmd)
		free(cmd->cmd);
	if (cmd->path)
		free(cmd->path);
	if (cmd->in_file)
		free(cmd->in_file);
	if (cmd->out_file)
		free(cmd->out_file);
	if (cmd->args)
	{
		while (cmd->args[i])
			free(cmd->args[i++]);
		free(cmd->args);
	}
	free(cmd);
}

void	free_cmd_list(t_data *shell)
{
	t_cmd	*cmd_lst_next;
	t_cmd	*cmd_lst;

	cmd_lst = shell->cmd_lst;
	if (cmd_lst)
	{
		while (cmd_lst)
		{
			cmd_lst_next = cmd_lst->next;
			free_cmd(cmd_lst);
			cmd_lst = cmd_lst_next;
		}
	}
	shell->cmd_lst = NULL;
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

void	free_all(t_data *shell)
{
	t_token	*next_token;

	if (shell->input)
		free(shell->input);
	if (shell->token_lst)
	{
		while (shell->token_lst)
		{
			if (shell->token_lst->str)
				free(shell->token_lst->str);
			next_token = shell->token_lst->next;
			free(shell->token_lst);
			shell->token_lst = next_token;
		}
	}
	free_cmd_list(shell);
}
