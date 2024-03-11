/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fail.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbeyer <frbeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 14:09:37 by mottjes           #+#    #+#             */
/*   Updated: 2024/03/11 15:24:47 by frbeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	malloc_fail(t_data *shell)
{
	ft_putstr_fd("minishell: no memory left on device\n", 2);
	free_all(shell);
	free_environment(shell);
	rl_clear_history();
	exit(1);
}

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
