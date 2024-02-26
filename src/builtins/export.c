/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:14:24 by mottjes           #+#    #+#             */
/*   Updated: 2024/02/26 16:01:50 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_export(t_data *shell)
{
	printf("declare -x\n");
}

void	export(t_data *shell, char *var)
{
	char	**new_envp;
	int		i;
	
	i = 0;	
	if (!var)
		return (print_export(shell));
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
	new_envp[i] = ft_strdup(var);
	new_envp[i + 1] = NULL;
	i = 0;
	while (shell->envp[i])
	{
		free(shell->envp[i]);
		i++;
	}
	free(shell->envp);
	shell->envp = new_envp;
}
