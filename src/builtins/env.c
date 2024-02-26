/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:14:28 by mottjes           #+#    #+#             */
/*   Updated: 2024/02/26 15:56:22 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	env(t_data *shell)
{
	int i;
	int	j;

	i = 0;
	while(shell->envp[i])
	{	
		j = 0;
		while (shell->envp[i][j] != '=' && shell->envp[i][j] != '\0')
			j++;
		if (shell->envp[i][j] == '=')
			printf("%s\n", shell->envp[i]);
		i++;
	}
}
