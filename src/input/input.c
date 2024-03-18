/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:50:04 by mottjes           #+#    #+#             */
/*   Updated: 2024/03/14 17:56:42 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern int	g_status;

void	input(t_data *shell)
{
	shell->restart = false;
	shell->input = readline("minishell $ ");
	if (!shell->input)
	{
		free_all(shell);
		free_environment(shell);
		rl_clear_history();
		shell->exit_status = 0;
		ft_putendl_fd("exit", 1);
		exit(shell->exit_status);
	}
	add_history(shell->input);
	if (g_status)
	{
		shell->exit_status = g_status + 128;
		g_status = 0;
	}
}
