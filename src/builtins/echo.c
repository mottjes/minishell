/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:14:30 by mottjes           #+#    #+#             */
/*   Updated: 2024/03/13 16:03:34 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
			ft_putstr_fd(cmd->args[i], shell->fd_built_in);
			if (cmd->args[i + 1])
				ft_putstr_fd(" ", shell->fd_built_in);
			i++;
		}
		if (ft_strncmp(cmd->args[1], "-n", 5))
			ft_putstr_fd("\n", shell->fd_built_in);
	}
	else
		ft_putendl_fd("", shell->fd_built_in);
	if (shell->exit_status != 1)
		shell->exit_status = 0;
}
