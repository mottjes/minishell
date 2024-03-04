/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:14:26 by mottjes           #+#    #+#             */
/*   Updated: 2024/03/04 16:37:14 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit(t_data *shell, t_cmd *cmd)
{
	int	i;

	i = 0;
	// free_all(shell);
	rl_clear_history();
	ft_putstr_fd("exit\n", 1);
	shell->exit_status = 0;
	if (cmd->args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		shell->exit_status = 1;
		exit(shell->exit_status);
	}
	if (cmd->args[1])
	{
		while (cmd->args[1][i])
		{
			if (cmd->args[1][i] < '0' || cmd->args[1][i] > '9')
			{
				ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
				shell->exit_status = 2;
				exit(shell->exit_status);
			}
			i++;
		}
		if (cmd->args[1])
		{
			i = ft_atoi(cmd->args[1]);
			shell->exit_status = i;
		}
	}
	exit(shell->exit_status);
}
