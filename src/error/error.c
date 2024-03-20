/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:39:08 by mottjes           #+#    #+#             */
/*   Updated: 2024/03/20 13:18:39 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pipe_fail(t_data *shell)
{
	ft_putstr_fd("minishell: pipe error\n", 2);
	free_all(shell);
	free_environment(shell);
	rl_clear_history();
	exit(1);
}

void	child_fail(t_data *shell)
{
	ft_putstr_fd("minishell: fork error\n", 2);
	free_all(shell);
	free_environment(shell);
	rl_clear_history();
	exit(1);
}

void	malloc_fail(t_data *shell)
{
	ft_putstr_fd("minishell: no memory left on device\n", 2);
	free_all(shell);
	free_environment(shell);
	rl_clear_history();
	exit(1);
}

void	*safe_malloc(size_t bytes, t_data *shell)
{
	void	*ptr;

	ptr = malloc(bytes);
	if (!ptr)
		malloc_fail(shell);
	return (ptr);
}
