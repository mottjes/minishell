/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:41:24 by mottjes           #+#    #+#             */
/*   Updated: 2024/03/14 15:52:55 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	env(t_data *shell, t_cmd *cmd)
{
	int	i;
	int	j;

	i = 0;
	if (cmd->args[1])
	{
		ft_putstr_fd("env: ‘", 2);
		ft_putstr_fd(cmd->args[1], 2);
		ft_putstr_fd("’: No such file or directory\n", 2);
		shell->exit_status = 127;
		return ;
	}
	while (shell->envp[i])
	{
		j = 0;
		while (shell->envp[i][j] != '=' && shell->envp[i][j] != '\0')
			j++;
		if (shell->envp[i][j] == '=')
			ft_putendl_fd(shell->envp[i], cmd->fd_out);
		i++;
	}
	shell->exit_status = 0;
}
