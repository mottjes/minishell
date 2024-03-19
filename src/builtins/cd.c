/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:41:14 by mottjes           #+#    #+#             */
/*   Updated: 2024/03/19 13:53:44 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	copy_old_pwd(t_data *shell, char *new_pwd)
{
	int	i;
	int	size;

	i = 0;
	while (shell->envp[i])
	{
		if (!ft_strncmp("OLDPWD=", shell->envp[i], 7))
		{
			free(shell->envp[i]);
			size = ft_strlen(new_pwd);
			shell->envp[i] = safe_malloc(sizeof(char) * (size + 8), shell);
			ft_strlcpy(shell->envp[i], "OLDPWD=", 8);
			ft_strlcpy(shell->envp[i] + 7, new_pwd, size + 1);
			return ;
		}
		i++;
	}
}

static void	update_old_pwd(t_data *shell)
{
	char	*new_pwd;
	int		i;

	i = 0;
	while (shell->envp[i])
	{
		if (!ft_strncmp("PWD=", shell->envp[i], 4))
		{
			new_pwd = ft_strdup(shell->envp[i] + 4);
			if (!new_pwd)
				malloc_fail(shell);
		}
		i++;
	}
	copy_old_pwd(shell, new_pwd);
}

static void	update_pwd(t_data *shell)
{
	char	*new_pwd;
	int		size;
	int		i;

	i = 0;
	while (shell->envp[i])
	{
		if (!ft_strncmp("PWD=", shell->envp[i], 4))
		{
			new_pwd = getcwd(NULL, 0);
			if (!new_pwd)
				malloc_fail(shell);
			size = ft_strlen(new_pwd);
			free(shell->envp[i]);
			shell->envp[i] = malloc(sizeof(char) * (size + 5));
			ft_strlcpy(shell->envp[i], "PWD=", 5);
			ft_strlcpy(shell->envp[i] + 4, new_pwd, size + 1);
			return ;
		}
		i++;
	}
}

void	cd(t_data *shell, t_cmd *cmd)
{
	char	*error;

	if (cmd->args[2])
	{
		shell->exit_status = 1;
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return ;
	}
	if (chdir(cmd->args[1]))
	{
		shell->exit_status = 1;
		error = ft_strjoin("minishell: cd: ", cmd->args[1]);
		perror(error);
		return ;
	}
	update_old_pwd(shell);
	update_pwd(shell);
	shell->exit_status = 0;
}
