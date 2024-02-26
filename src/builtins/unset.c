/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:14:20 by mottjes           #+#    #+#             */
/*   Updated: 2024/02/26 15:15:38 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	unset(t_data *shell, char *var)
{
	char	**new_envp;
	int		size;
	int		i;
	int		j;

	i = 0;
	j = 0;
	size = 0;
	while (shell->envp[size])
		size++;
	while (shell->envp[i])
	{
		if (!ft_strncmp(var, shell->envp[i], ft_strlen(var)))
		{
			printf("\n\n\n found envvar %i \n\n\n", i);
			new_envp = malloc(sizeof(char *) * size + 1);
			if (!shell->envp)
				malloc_fail(shell);
			while (j < i)
			{
				new_envp[j] = ft_strdup(shell->envp[j]);
				j++;
			}
			while (j < size - 1)
			{
				new_envp[j] = ft_strdup(shell->envp[j + 1]);
				j++;
			}
			new_envp[j] = NULL;
			i = 0;
			while (shell->envp[i])
			{
				free(shell->envp[i]);
				i++;
			}
			shell->envp = new_envp;
			break ;
		}
		i++;
	}
}
