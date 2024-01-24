/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 14:37:41 by mottjes           #+#    #+#             */
/*   Updated: 2024/01/24 14:37:23 by mottjes          ###   ########.fr       */
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

/*
readline functions:
readline, -> reads line puts promt
rl_clear_history, -> clears input history
rl_on_new_line,	-> Tell the update functions that we have moved onto a new (empty) line, usually after outputting a newline.
rl_replace_line, -> Replace the contents of rl_line_buffer with text. The point and mark are preserved, if possible. If clear_undo is non-zero, the undo list associated with the current line is cleared.
rl_redisplay, -> Change what’s displayed on the screen to reflect the current contents of rl_line_buffer.
add_history, ->adds history
*/
/*
ctrl-C displays a new prompt on a new line. (SIGINT)
◦ ctrl-D exits the shell.
◦ ctrl-\ does nothing

signal,
sigaction, 
sigemptyset, 
sigaddset, 
kill, 
exit
*/