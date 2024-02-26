/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:14:24 by mottjes           #+#    #+#             */
/*   Updated: 2024/02/26 17:30:29 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_export(t_data *shell)
{
	char	*temp;
	int		size;
	int		i;
	int		j;

	i = 0;
	size = 0;
	if (shell->envp == NULL)
		return ;
	while (shell->envp[size])
		size++;
	while (i < size -1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strncmp(shell->envp[j], shell->envp[j + 1], ft_strlen(shell->envp[j] + 1)) > 0)
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
	while (shell->envp[i])
	{
		printf("declare -x %s\n", shell->envp[i]);
		i++;
	}
}

static	int	valid_argument(char *var)
{
	int	i;

	i = 1;
	if ((var[0] < 'A' || var[0] > 'Z') && (var[0] < 'a' || var[0] > 'z'))
		return (0);
	while (var[i] != '=')
	{
		if ((var[i] < 'A' || var[i] > 'Z') && (var[i] < 'a' || var[i] > 'z'))
		{
			if ((var[i] < '0' || var[i] > '9') && var[i] != '_')
				return (0);
		}
		i++;
	}
	return (1);	
}

void	export(t_data *shell, char *var)
{
	char	**new_envp;
	int		i;
	
	i = 0;	
	if (!var)
		return (print_export(shell));
	if (!valid_argument(var))
	{
		printf("minishell: export: `%s': not a valid identifier\n", var);
		return ;
	}
	while (shell->envp[i])
	{
		if (!ft_strncmp(var, shell->envp[i], ft_strlen(var)))
			return ;
		i++;
	}
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
