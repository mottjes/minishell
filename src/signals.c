/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 14:37:41 by mottjes           #+#    #+#             */
/*   Updated: 2024/01/18 14:40:13 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	signal_handler(int signal)
{
	if (signal == SIGQUIT)
		return ;
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = &signal_handler;
	if (sigaction(SIGINT, &sa, NULL) == - 1)
		return ;									//error handling
	if (sigaction(SIGQUIT, &sa, NULL) == - 1)
		return ;									//error handling	
}
