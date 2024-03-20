/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 21:07:09 by mottjes           #+#    #+#             */
/*   Updated: 2024/03/20 13:26:21 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	builtin_check(t_cmd *cmd_lst)
{
	while (cmd_lst)
	{
		if (!ft_strncmp(cmd_lst->cmd, "echo", ft_strlen(cmd_lst->cmd)))
			cmd_lst->builtin = true;
		else if (!ft_strncmp(cmd_lst->cmd, "cd", ft_strlen(cmd_lst->cmd)))
			cmd_lst->builtin = true;
		else if (!ft_strncmp(cmd_lst->cmd, "pwd", ft_strlen(cmd_lst->cmd)))
			cmd_lst->builtin = true;
		else if (!ft_strncmp(cmd_lst->cmd, "export", ft_strlen(cmd_lst->cmd)))
			cmd_lst->builtin = true;
		else if (!ft_strncmp(cmd_lst->cmd, "unset", ft_strlen(cmd_lst->cmd)))
			cmd_lst->builtin = true;
		else if (!ft_strncmp(cmd_lst->cmd, "env", ft_strlen(cmd_lst->cmd)))
			cmd_lst->builtin = true;
		else if (!ft_strncmp(cmd_lst->cmd, "exit", ft_strlen(cmd_lst->cmd)))
			cmd_lst->builtin = true;
		cmd_lst = cmd_lst->next;
	}
}

static void	cmd_get_path(t_data *shell, t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->builtin == false)
		{
			if (!check_path_given(shell, cmd))
			{
				search_path(shell, cmd);
				if (!cmd->path)
				{
					ft_putstr_fd("minishell: ", 2);
					ft_putstr_fd(cmd->cmd, 2);
					ft_putstr_fd(": command not found\n", 2);
					shell->exit_status = 127;
					shell->restart = true;
					return ;
				}
				if (access(cmd->path, X_OK) == -1)
				{
					ft_putstr_fd("minishell: ", 2);
					ft_putstr_fd(cmd->cmd, 2);
					ft_putstr_fd(": Permission denied\n", 2);
					shell->exit_status = 126;
					shell->restart = true;
					return ;
				}
			}
			cmd = cmd->next;
		}
		else
			cmd = cmd->next;
	}
}

void	parser(t_data *shell)
{
	if (shell->restart == true)
		return ;
	syntax_commands(shell->token_lst, &shell->restart);
	syntax_redirections(shell->token_lst, &shell->restart);
	if (shell->restart == true)
	{
		shell->exit_status = 2;
		return ;
	}
	init_cmd_table(shell);
	builtin_check(shell->cmd_lst);
	cmd_get_path(shell, shell->cmd_lst);
}
