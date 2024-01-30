/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:53:35 by mottjes           #+#    #+#             */
/*   Updated: 2024/01/30 12:01:23 by mottjes          ###   ########.fr       */
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

void	cmd_get_path(t_cmd *cmds, char **envp, t_error *error)
{
	char **env_paths;
	char *cmd_mod;
	char *cmd_path;
	int i;

	i = 0;
	while (cmds)
	{
		if (!cmds->builtin)
		{
			if (cmds->cmd[0] == '/')
			{
				cmds->path = ft_strdup(cmds->cmd);
				if(!cmds->path)
				{
					*error = malloc_failed;
					return ;
				}
			}
			else
			{
				while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
					i++;
				env_paths = ft_split(envp[i] + 5, ':');
				if(!env_paths)
				if(!cmds->path)
				{
					*error = malloc_failed;
					return ;
				}
				cmd_mod = ft_strjoin("/", cmds->cmd);
				if (!cmd_mod)
				if(!cmds->path)
				{
					*error = malloc_failed;
					return ;
				}
				i = 0;
				while (env_paths[i])
				{
					cmd_path = ft_strjoin(env_paths[i], cmd_mod);
					if (!cmd_path)
					if(!cmds->path)
					{
						*error = malloc_failed;
						return ;
					}
					if (!access(cmd_path, F_OK))
					{
						cmds->path = cmd_path;
						break ;
					}
					i++;
				}
				i = 0;
			}
			if (!cmds->path)
			{
				*error = command_not_found;
				return ;
			}
		}
		cmds = cmds->next;
	}
}

void	parser(t_data *shell)
{
	if (shell->restart)
		return ;
	//syntax_check(shell->token_list);
	cmd_table_init(shell);
	builtin_check(shell->cmd_list);
	cmd_get_path(shell->cmd_list, shell->envp, &shell->error);
}
