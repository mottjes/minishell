/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:57:07 by mottjes           #+#    #+#             */
/*   Updated: 2024/03/14 15:58:12 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	create_new_envp(t_data *shell, char ***ptr, int j)
{
	char	**new_envp;
	int		i;

	i = 0;
	new_envp = *ptr;
	while (i < j)
	{
		new_envp[i] = ft_strdup(shell->envp[i]);
		if (!new_envp[i])
			malloc_fail(shell);
		i++;
	}
	i++;
	while (shell->envp[i])
	{
		new_envp[i - 1] = ft_strdup(shell->envp[i]);
		if (!new_envp[i - 1])
			malloc_fail(shell);
		i++;
	}
	new_envp[i - 1] = NULL;
	free_environment(shell);
	shell->envp = new_envp;
}

void	delete_env_var(t_data *shell, int j)
{
	char	**new_envp;
	int		i;

	i = 0;
	while (shell->envp[i])
		i++;
	new_envp = safe_malloc(sizeof(char *) * i + 1, shell);
	create_new_envp(shell, &new_envp, j);
}

void	sort_envp(t_data *shell, int size)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < size -1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strncmp(shell->envp[j], shell->envp[j + 1],
					ft_strlen(shell->envp[j] + 1)) > 0)
			{
				temp = shell->envp[j];
				shell->envp[j] = shell->envp[j + 1];
				shell->envp[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
	i = 0;
}
