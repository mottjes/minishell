/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mika <mika@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:41:21 by mottjes           #+#    #+#             */
/*   Updated: 2024/09/26 19:02:41 by mika             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_n(t_cmd *cmd, bool *n_flag)
{
	int	i;
	int	j;

	i = 1;
	while (cmd->args[i])
	{
		j = 1;
		if (!ft_strncmp(cmd->args[i], "-n", 2))
		{
			while (cmd->args[i][j] == 'n')
				j++;
			if (cmd->args[i][j] == '\0')
			{
				*n_flag = true;
				i++;
			}
			else
				break ;
		}
		else
			break ;
	}
	return (i);
}

void	echo(t_data *shell, t_cmd *cmd)
{
	int		i;
	bool	n_flag;

	i = 1;
	n_flag = false;
	if (cmd->args[1])
	{
		i = check_n(cmd, &n_flag);
		while (cmd->args[i])
		{
			ft_putstr_fd(cmd->args[i], cmd->fd_out);
			if (cmd->args[i + 1])
				ft_putstr_fd(" ", cmd->fd_out);
			i++;
		}
		if (n_flag == false)
			ft_putstr_fd("\n", cmd->fd_out);
	}
	else
		ft_putendl_fd("", cmd->fd_out);
	shell->exit_status = 0;
}
