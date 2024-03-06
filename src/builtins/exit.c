/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:14:26 by mottjes           #+#    #+#             */
/*   Updated: 2024/03/06 17:43:52 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit(t_data *shell, t_cmd *cmd)
{
	int	i;

	i = 0;
	shell->exit_status = 0;
	ft_putstr_fd("exit\n", 1);
	if (cmd->args[1])
	{
		i = ft_atoi(cmd->args[1]);
		shell->exit_status = i;
		while (cmd->args[1][i])
		{
			if (cmd->args[1][i] < '0' || cmd->args[1][i] > '9')
			{
				ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
				shell->exit_status = 2;
				break ;
			}
			i++;
		}
	}
	if (!cmd->args[1][i] && cmd->args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		shell->exit_status = 1;
	}
	rl_clear_history();
	free_all(shell);
	free_environment(shell);
	exit(shell->exit_status);
}
