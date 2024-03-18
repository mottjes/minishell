/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:38:51 by mottjes           #+#    #+#             */
/*   Updated: 2024/03/14 17:29:47 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_status;

static void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		g_status = signal;
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	signal_handler_child(int signal)
{
	if (signal == SIGINT)
	{
		g_status = signal;
		rl_replace_line("", 0);
		write(1, "\n", 1);
	}
}

void	signals_child(void)
{
	signal(SIGINT, &signal_handler_child);
	signal(SIGQUIT, SIG_IGN);
}

void	signals(void)
{
	signal(SIGINT, &signal_handler);
	signal(SIGQUIT, SIG_IGN);
}
