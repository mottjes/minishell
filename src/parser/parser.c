/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:53:35 by mottjes           #+#    #+#             */
/*   Updated: 2024/03/13 12:50:05 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin_check(t_cmd *cmd_list)
{
	cmd_list->builtin = 0;
	while (cmd_list)
	{
		if (!ft_strncmp(cmd_list->cmd, "echo", ft_strlen(cmd_list->cmd)))
			cmd_list->builtin = 1;
		else if (!ft_strncmp(cmd_list->cmd, "cd", ft_strlen(cmd_list->cmd)))
			cmd_list->builtin = 1;
		else if (!ft_strncmp(cmd_list->cmd, "pwd", ft_strlen(cmd_list->cmd)))
			cmd_list->builtin = 1;
		else if (!ft_strncmp(cmd_list->cmd, "export", ft_strlen(cmd_list->cmd)))
			cmd_list->builtin = 1;
		else if (!ft_strncmp(cmd_list->cmd, "unset", ft_strlen(cmd_list->cmd)))
			cmd_list->builtin = 1;
		else if (!ft_strncmp(cmd_list->cmd, "env", ft_strlen(cmd_list->cmd)))
			cmd_list->builtin = 1;
		else if (!ft_strncmp(cmd_list->cmd, "exit", ft_strlen(cmd_list->cmd)))
			cmd_list->builtin = 1;
		cmd_list = cmd_list->next;
	}
}

int	path_given(t_data *shell, t_cmd *cmds)
{
	if (cmds->cmd[0] == '/')
	{
		cmds->path = ft_strdup(cmds->cmd);
		if (!cmds->path)
			malloc_fail(shell);
		if (access(cmds->path, F_OK))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmds->cmd, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			shell->exit_status = 127;
			shell->restart = 1;
			return (1);
		}
	}
	return (0);
}

void	search_path(t_data *shell, t_cmd *cmds)
{
	char	**env_paths;
	char	*cmd_mod;
	char	*cmd_path;
	int		i;

	i = 0;
	while (shell->envp[i] && ft_strncmp(shell->envp[i], "PATH=", 5))
		i++;
	env_paths = ft_split(shell->envp[i] + 5, ':');
	cmd_mod = ft_strjoin("/", cmds->cmd);
	if (!cmd_mod || !env_paths)
		malloc_fail(shell);
	i = 0;
	while (env_paths[i])
	{
		cmd_path = ft_strjoin(env_paths[i], cmd_mod);
		if (!cmd_path)
			malloc_fail(shell);
		if (!access(cmd_path, F_OK))
		{
			cmds->path = cmd_path;
			break ;
		}
		i++;
	}
}

void	cmd_get_path(t_cmd *cmds, t_data *shell)
{
	while (cmds)
	{
		if (!cmds->builtin)
		{
			if (path_given(shell, cmds))
				return ;
			else
			{
				search_path(shell, cmds);
				if (!cmds->path)
				{
					ft_putstr_fd("minishell: ", 2);
					ft_putstr_fd(cmds->cmd, 2);
					ft_putstr_fd(": command not found\n", 2);
					shell->exit_status = 127;
					shell->restart = 1;
					return ;
				}
			}
		}
		cmds = cmds->next;
	}
}

void	parser(t_data *shell)
{
	if (shell->restart)
		return ;
	syntax_commands(shell->token_list, &shell->restart);
	syntax_redirections(shell->token_list, &shell->restart);
	// syntax_pipe(shell->token_list, &shell->restart);
	if (shell->restart)
	{
		shell->exit_status = 2;
		return ;
	}
	cmd_table_init(shell);
	builtin_check(shell->cmd_list);
	cmd_get_path(shell->cmd_list, shell);
}
