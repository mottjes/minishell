/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   promt.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:36:17 by mottjes           #+#    #+#             */
/*   Updated: 2024/01/30 13:25:41 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_promt(t_data *shell)
{
	char *cwd;
	int i;

	i = 0;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return ;					//errror handling
	while (cwd[i])
		i++;
	while (cwd[i - 1] != '/')
		i--;
	printf(CYAN BOLD"%s", cwd + i);
	free(cwd);
	shell->input = readline(" % " RESET);
	if (!shell->input)
		shell->restart = 1;
	add_history(shell->input);
}
