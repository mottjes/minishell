/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mika <mika@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 21:07:09 by mottjes           #+#    #+#             */
/*   Updated: 2024/09/26 19:23:53 by mika             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	check_path_given(t_data *shell, t_cmd *cmd)
{
	struct stat	filestat;

	if (cmd->cmd[0] == '/' || (cmd->cmd[0] == '.' && cmd->cmd[1] == '/'))
	{
		cmd->path = ft_strdup(cmd->cmd);
		if (!cmd->path)
			malloc_fail(shell);
		if (access(cmd->path, F_OK))
			return (print_error_2(shell, cmd, 1), true);
		else
		{
			if (stat(cmd->path, &filestat) == 0)
			{
				if (S_ISDIR(filestat.st_mode))
					return (print_error_2(shell, cmd, 2), true);
			}
		}
	}
	return (false);
}

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

static void	print_error_1(t_data *shell, t_cmd *cmd, int error_nbr)
{
	if (error_nbr == 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		shell->exit_status = 127;
		shell->restart = true;
		return ;
	}
	if (error_nbr == 2)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->cmd, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		shell->exit_status = 126;
		shell->restart = true;
		return ;
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
				search_path(shell, cmd, 0);
				if (!cmd->path)
					return (print_error_1(shell, cmd, 1));
				if (access(cmd->path, X_OK) == -1)
					return (print_error_1(shell, cmd, 2));
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
	if (!shell->restart)
		syntax_pipes(shell->token_lst, &shell->restart);
	if (shell->restart == true)
	{
		shell->exit_status = 2;
		return ;
	}
	init_cmd_table(shell);
	builtin_check(shell->cmd_lst);
	cmd_get_path(shell, shell->cmd_lst);
}
