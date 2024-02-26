/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:39:29 by mottjes           #+#    #+#             */
/*   Updated: 2024/02/26 17:35:41 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_shlvl(t_data *shell)
{
	char	*shlvlp;
	int		shlvl;
	int		i;

	i = 0;
	while (shell->envp[i])
	{
		if (!ft_strncmp(shell->envp[i], "SHLVL=", 6))
		{
			shlvl = ft_atoi(shell->envp[i] + 6);
			shlvl++;
			shlvlp = ft_itoa(shlvl);
			ft_strlcpy(shell->envp[i] + 6, shlvlp, ft_strlen(shlvlp) + 1);
		}
		i++;
	}
}

void	create_environment(t_data *shell, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	shell->envp = malloc(sizeof(char *) * (i + 1));
	if (!shell->envp)
		malloc_fail(shell);
	i = 0;
	while (envp[i])
	{
		shell->envp[i] = ft_strdup(envp[i]);
		i++;
	}
	shell->envp[i] = NULL;
	set_shlvl(shell);
}
