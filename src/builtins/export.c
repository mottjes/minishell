/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:14:24 by mottjes           #+#    #+#             */
/*   Updated: 2024/03/12 13:50:50 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	valid_argument(char *var)
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

void	print_export(t_data *shell)
{
	int		size;
	int		i;

	i = 0;
	size = 0;
	if (!shell->envp)
		return ;
	while (shell->envp[size])
		size++;
	sort_envp(shell, size);
	while (shell->envp[i])
	{
		printf("declare -x %s\n", shell->envp[i]);
		i++;
	}
}

void	add_env_var(t_data *shell, t_cmd *cmd, int j)
{
	char	**new_envp;
	int		i;

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
	free_environment(shell);
	shell->envp = new_envp;
}

void	compare_to_env_vars(t_data *shell, t_cmd *cmd, int i)
{
	int	j;
	int	k;

	j = 0;
	while (shell->envp[j])
	{
		k = 0;
		while (cmd->args[i][k])
		{
			if (cmd->args[i][k] == shell->envp[j][k])
				k++;
			else
				break ;
			if (cmd->args[i][k] == '=' || cmd->args[i][k] == '\0')
			{
				delete_env_var(shell, j);
				break ;
			}
		}
		j++;
	}
}

void	export(t_data *shell, t_cmd *cmd)
{
	int	i;

	i = 1;
	if (!cmd->args[1])
		return (print_export(shell));
	while (cmd->args[i])
	{
		if (!valid_argument(cmd->args[i]))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(cmd->args[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			shell->exit_status = 1;
			return ;
		}
		compare_to_env_vars(shell, cmd, i);
		add_env_var(shell, cmd, i);
		i++;
	}
	shell->exit_status = 0;
}
