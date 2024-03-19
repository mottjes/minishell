/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:41:35 by mottjes           #+#    #+#             */
/*   Updated: 2024/03/19 13:55:04 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	void	unset_env_var(t_data *shell, int size, int i)
{
	char	**new_envp;
	int		j;

	j = 0;
	new_envp = safe_mallocsizeof(sizeof(char *) * size + 1, shell);
	while (j < i)
	{
		new_envp[j] = ft_strdup(shell->envp[j]);
		if (!new_envp[j])
			malloc_fail(shell);
		j++;
	}
	while (j < size - 1)
	{
		new_envp[j] = ft_strdup(shell->envp[j + 1]);
		if (!new_envp[j])
			malloc_fail(shell);
		j++;
	}
	new_envp[j] = NULL;
	i = 0;
	while (shell->envp[i])
		free(shell->envp[i++]);
	free(shell->envp);
	shell->envp = new_envp;
}

void	unset(t_data *shell, t_cmd *cmd)
{
	int		size;
	int		i;
	int		k;

	k = 0;
	while (cmd->args[k])
	{
		i = 0;
		size = 0;
		while (shell->envp[size])
			size++;
		while (shell->envp[i])
		{
			if (!ft_strncmp(cmd->args[k], shell->envp[i],
					ft_strlen(cmd->args[k])))
			{
				unset_env_var(shell, size, i);
				break ;
			}
			i++;
		}
		k++;
	}
	shell->exit_status = 0;
}
