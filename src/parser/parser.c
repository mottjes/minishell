/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:53:35 by mottjes           #+#    #+#             */
/*   Updated: 2024/01/24 19:47:14 by mottjes          ###   ########.fr       */
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

void	cmd_get_path(t_cmd *cmds, char **envp)
{
	char *cmd_path;
	char **envp_paths;
	int i;

	i = 0;
	if (cmds->cmd[i] == '/')
	{
		cmds->path = ft_strdup(cmds->cmd);
		if(!cmds->path)
			return ;									//error handling
	}
	else
	{
		while (ft_strncmp(envp[i], "PATH=", 5) && envp[i])
			i++;
		envp_paths = ft_split(envp[i] + 5, ':');
		if(!envp_paths)
			return ;									//error handling
		i = 0;
		while (envp_paths[i])
		{
			cmd_path = ft_strjoin("/", cmds->cmd);
			if (!cmd_path)
				return ;								//error handling
			cmd_path = ft_strjoin(envp_paths[i], cmd_path);
			if (!cmd_path)
				return ;								//error handling
			if (!access(cmd_path, F_OK))
			{
				cmds->path = cmd_path;
				break ;
			}	
			i++;
		}
	}
		
}

void	parser(t_data *shell)
{
	if (shell->restart)
		return ;
	//syntax_check(shell->token_list);
	cmd_table_init(shell);
	builtin_check(shell->cmd_list);
	cmd_get_path(shell->cmd_list, shell->envp);
}
