/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:14:24 by mottjes           #+#    #+#             */
/*   Updated: 2024/02/26 15:15:50 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	export(t_data *shell, char *var)
{
	// no arguments -> prints the env list in alphabetical order (+ declare -x)
	// adds variable to the list
	char	**new_envp;
	int		i;
	
	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	if (var[i] != '=')
		return ;
	i = 0;	
	while (shell->envp[i])
		i++;
	new_envp = malloc(sizeof(char *) * i + 2);
	if (!new_envp)
		malloc_fail(shell);
	i = 0;
	while (shell->envp[i])
	{
		new_envp[i] = ft_strdup(shell->envp[i]);
		i++;
	}
	new_envp[i] = ft_strdup("TEST=TEST");
	new_envp[i + 1] = NULL;
}
