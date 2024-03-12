/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:45:56 by mottjes           #+#    #+#             */
/*   Updated: 2024/03/12 17:51:39 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_status;

void	input(t_data *shell)
{
	shell->restart = 0;
	shell->input = readline("minishell $ ");
	if (!shell->input)
	{
		shell->exit_status = 0;
		free_all(shell);
		free_environment(shell);
		ft_putstr_fd("exit\n", 1);
		exit(shell->exit_status);
	}
	if (g_status)
	{
		shell->exit_status = g_status + 128;
		g_status = 0;
	}
	add_history(shell->input);
}
