/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:45:56 by mottjes           #+#    #+#             */
/*   Updated: 2024/03/04 17:12:44 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	input(t_data *shell)
{
	shell->restart = 0;
	shell->input = readline("minishell $ ");
	if (!shell->input)
		shell->restart = 1;
	add_history(shell->input);
}
