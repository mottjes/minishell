/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mika <mika@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 17:39:01 by mottjes           #+#    #+#             */
/*   Updated: 2024/09/26 18:23:43 by mika             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	void	shlvl_to_high(int *shlvl)
{
	ft_putstr_fd("bash: warning: shell level (", 2);
	ft_putnbr_fd(*shlvl, 2);
	ft_putstr_fd(") too high, resetting to 1\n", 2);
	*shlvl = 1;
}

static void	set_shlvl(t_data *shell)
{
	char	*shlvl_str;
	int		shlvl_len;
	int		shlvl;
	int		i;

	i = 0;
	while (shell->envp[i])
	{
		if (!ft_strncmp(shell->envp[i], "SHLVL=", 6))
		{
			shlvl = ft_atoi(shell->envp[i] + 6);
			shlvl++;
			if (shlvl > 999)
				shlvl_to_high(&shlvl);
			shlvl_str = ft_itoa(shlvl);
			free(shell->envp[i]);
			shlvl_len = ft_strlen(shlvl_str);
			shell->envp[i] = safe_malloc(sizeof(char) * shlvl_len + 7, shell);
			ft_strlcpy(shell->envp[i], "SHLVL=", 7);
			ft_strlcpy(shell->envp[i] + 6, shlvl_str, shlvl_len + 1);
			free(shlvl_str);
			return ;
		}
		i++;
	}
}

void	init_environment(t_data *shell, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	shell->envp = safe_malloc(sizeof (char *) * (i + 1), shell);
	i = 0;
	while (envp[i])
	{
		shell->envp[i] = ft_strdup(envp[i]);
		i++;
	}
	shell->envp[i] = NULL;
	set_shlvl(shell);
}
