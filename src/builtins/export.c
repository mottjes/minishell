/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:14:24 by mottjes           #+#    #+#             */
/*   Updated: 2024/03/06 16:09:16 by mottjes          ###   ########.fr       */
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
	while (var[i] != '=' && var[i])
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

static	void	delete_env_var(t_data *shell, int i)
{
	char	**new_envp;
	int		j;
	
	j = 0;
	while (shell->envp[j])
		j++;
	new_envp = malloc(sizeof(char *) * j);
	if (!new_envp)
		malloc_fail(shell);
	j = 0;
	while (j < i)
	{
		new_envp[j] = ft_strdup(shell->envp[j]);
		if (!new_envp[j])
			malloc_fail(shell);
		j++;
	}
	j++;
	while (shell->envp[j])
	{
		new_envp[j - 1] = ft_strdup(shell->envp[j]);
		if (!new_envp[j - 1])
			malloc_fail(shell);
		j++;
	}
	new_envp[j - 1] = NULL;
	while (shell->envp[i])
	{
		free(shell->envp[i]);
		i++;
	}
	free(shell->envp);
	shell->envp = new_envp;
}

void	export(t_data *shell, t_cmd *cmd)
{
	char	**new_envp;
	int		i;
	int		j;
	int		k;

	j = 1;
	if (!cmd->args[1])
		return (print_export(shell));
	while (cmd->args[j])
	{
		i = 0;
		new_envp = NULL;
		if (!valid_argument(cmd->args[j]))
		{
			printf("minishell: export: `%s': not a valid identifier\n", cmd->args[j]);
			shell->exit_status = 1;
			return ;
		}
		while (shell->envp[i])
		{
			k = 0;
			while (cmd->args[j][k])
			{
				if (cmd->args[j][k] == shell->envp[i][k])
					k++;
				else
					break ;
				if (cmd->args[j][k] == '=' || cmd->args[j][k] == '\0')
				{
					delete_env_var(shell, i);
					break ;
				}
			}
			i++;
		}
		i = 0;
		while (shell->envp[i])
			i++;
		new_envp = malloc(sizeof(char *) * (i + 2));
		if (!new_envp)
			malloc_fail(shell);
		i = 0;
		while (shell->envp[i])
		{
			new_envp[i] = ft_strdup(shell->envp[i]);
			i++;
		}
		new_envp[i] = ft_strdup(cmd->args[j]);
		new_envp[i + 1] = NULL;
		i = 0;
		while (shell->envp[i])
		{
			free(shell->envp[i]);
			i++;
		}
		free(shell->envp);
		shell->envp = new_envp;
		j++;
	}
	shell->exit_status = 0;
}
