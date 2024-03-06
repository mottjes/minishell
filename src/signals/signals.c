/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 14:37:41 by mottjes           #+#    #+#             */
/*   Updated: 2024/03/06 15:18:32 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int g_status;

void	signal_handler(int signal)
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

void	signal_handler_child(int signal)
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
	signal(SIGQUIT, SIG_IGN);								//error handling	
}

void	signals(void)
{
	signal(SIGINT, &signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

/*

ctrl-C displays a new prompt on a new line. (SIGINT)
ctrl-D exits the shell.
ctrl-\ does nothing
*/