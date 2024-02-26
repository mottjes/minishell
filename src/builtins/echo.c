/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:14:30 by mottjes           #+#    #+#             */
/*   Updated: 2024/02/26 15:15:26 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	echo(t_data *shell, int flag)
{
	if (flag == 0)
		ft_putstr_fd(shell->cmd_list->args[2], 1);
	if (flag == 1)
	{
		ft_putstr_fd(shell->cmd_list->args[1], 1);
		ft_putstr_fd("\n", 1);
	}
}
