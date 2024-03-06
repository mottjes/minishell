/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:45:56 by mottjes           #+#    #+#             */
/*   Updated: 2024/03/06 15:14:46 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	input(t_data *shell)
{
	shell->restart = 0;
	shell->input = readline("minishell $ ");
	if (!shell->input)
	{
		shell->exit_status = 0;
		// free_all(shell);
		ft_putstr_fd("exit\n", 1);
		exit(0);
	}
	add_history(shell->input);
}
