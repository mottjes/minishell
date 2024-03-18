/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:41:21 by mottjes           #+#    #+#             */
/*   Updated: 2024/03/18 17:13:36 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	echo(t_data *shell, t_cmd *cmd)
{
	int	i;

	i = 1;
	if (cmd->args[1])
	{
		if (!ft_strncmp(cmd->args[1], "-n", 5))
			i++;
		while (cmd->args[i])
		{
			ft_putstr_fd(cmd->args[i], cmd->fd_out);
			if (cmd->args[i + 1])
				ft_putstr_fd(" ", cmd->fd_out);
			i++;
		}
		if (ft_strncmp(cmd->args[1], "-n", 5))
			ft_putstr_fd("\n", cmd->fd_out);
	}
	else
		ft_putendl_fd("", cmd->fd_out);
	shell->exit_status = 0;
}
