/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:02:31 by frbeyer           #+#    #+#             */
/*   Updated: 2024/03/13 15:15:03 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_built_in(t_data *shell, t_cmd *cmd)
{
	if (!ft_strncmp(cmd->cmd, "echo", 4))
		echo(shell, cmd);
	else if (!ft_strncmp(cmd->cmd, "cd", 2))
		cd(shell, cmd);
	else if (!ft_strncmp(cmd->cmd, "pwd", 3))
		pwd(shell);
	else if (!ft_strncmp(cmd->cmd, "export", 6))
		export(shell, cmd);
	else if (!ft_strncmp(cmd->cmd, "unset", 3))
		unset(shell, cmd);
	else if (!ft_strncmp(cmd->cmd, "env", 5))
		env(shell, cmd);
	else if (!ft_strncmp(cmd->cmd, "exit", 5))
		ft_exit(shell, cmd);
}
