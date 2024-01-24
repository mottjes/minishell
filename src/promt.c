/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   promt.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:36:17 by mottjes           #+#    #+#             */
/*   Updated: 2024/01/24 18:16:05 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_promt(t_data *shell)
{
	shell->input = readline(CYAN BOLD "minishell % " RESET);
	if (!shell->input)
		shell->restart = 1;
}
