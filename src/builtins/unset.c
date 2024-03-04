/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:14:20 by mottjes           #+#    #+#             */
/*   Updated: 2024/03/04 17:00:01 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	unset(t_data *shell, t_cmd *cmd)
{
	char	**new_envp;
	int		size;
	int		i;
	int		j;
	int		k;
	
	k = 0;
	while (cmd->args[k])
	{
		i = 0;
		j = 0;
		size = 0;
		while (shell->envp[size])
			size++;
		while (shell->envp[i])
		{
			if (!ft_strncmp(cmd->args[k], shell->envp[i], ft_strlen(cmd->args[k])))
			{
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
				free(shell->envp);
				shell->envp = new_envp;
				break ;
			}
			i++;
		}
		k++;
	}
	shell->exit_status = 0;
}
