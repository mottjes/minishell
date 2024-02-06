/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 14:09:37 by mottjes           #+#    #+#             */
/*   Updated: 2024/02/06 14:41:59 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//void	free_all(t_data *shell)


void	error_check(t_data *shell)
{
	if (shell->error)
	{
		shell->restart = 1;
		if (shell->error == malloc_failed)
			ft_putstr_fd("minishell: malloc failed\n", 2);
		if (shell->error == quotes_not_closed)
			ft_putstr_fd("minishell: quotes not closed\n", 2);
		if (shell->error == command_not_found)
			ft_putstr_fd("minishell: command not found\n", 2);
		if (shell->error == env_var_not_found)
			ft_putstr_fd("minishell: environment variable not found\n", 2);
		if (shell->error == syntax_error)
			ft_putstr_fd("minishell: syntax error\n", 2);
	}
}

void	malloc_fail(t_data *shell)
{
	shell->error = malloc_failed;
	
	if (shell->error == malloc_failed)
		ft_putstr_fd("minishell: malloc failed\n", 2);
	exit(1);
}
