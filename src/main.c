/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:38:56 by mottjes           #+#    #+#             */
/*   Updated: 2024/03/18 15:29:24 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	shell;

	(void)argc;
	(void)argv;
	ft_memset(&shell, 0, sizeof(t_data));
	init_environment(&shell, envp);
	signals();
	while (1)
	{
		input(&shell);
		expander(&shell);
		lexer(&shell);
		parser(&shell);
		executor(&shell);
		free_all(&shell);
	}
}

// signals_child