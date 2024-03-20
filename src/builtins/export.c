/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:41:29 by mottjes           #+#    #+#             */
/*   Updated: 2024/03/20 13:16:40 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	valid_argument(char *var)
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

static void	print_export(t_data *shell, t_cmd *cmd)
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
		ft_putstr_fd("declare -x ", cmd->fd_out);
		ft_putendl_fd(shell->envp[i], cmd->fd_out);
		i++;
	}
}

static void	add_env_vars(t_data *shell, t_cmd *cmd, int j)
{
	char	**new_envp;
	int		i;

	i = 0;
	while (shell->envp[i])
		i++;
	new_envp = safe_malloc(sizeof(char *) * (i + 2), shell);
	i = 0;
	while (shell->envp[i])
	{
		new_envp[i] = ft_strdup(shell->envp[i]);
		i++;
	}
	new_envp[i] = ft_strdup(cmd->args[j]);
	if (!new_envp[i])
		malloc_fail(shell);
	new_envp[i + 1] = NULL;
	free_environment(shell);
	shell->envp = new_envp;
}

static void	compare_to_env_vars(t_data *shell, t_cmd *cmd, int i)
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
		return (print_export(shell, cmd));
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
		add_env_vars(shell, cmd, i);
		i++;
	}
	shell->exit_status = 0;
}
