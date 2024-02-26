/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 14:48:01 by mottjes           #+#    #+#             */
/*   Updated: 2024/02/26 14:31:54 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pwd(t_data *shell)
{
	char *cwd;
	
	cwd = getcwd(NULL, 0);
	if (!cwd)
		malloc_fail(shell);
	printf("%s\n", cwd);
	free(cwd);
}

void	env(char *envp[])
{
	char *env_variable;
	int i;

	i = 0;
	env_variable = envp[i];
	while(env_variable)
	{	
		printf("%s\n", env_variable);
		i++;
		env_variable = envp[i];
	}
}

void	echo(t_data *shell, int flag)
{
	if (flag == 0)
		ft_putstr_fd(shell->cmd_list->args[2], 1);
	if (flag == 1)
	{
		ft_putstr_fd(shell->cmd_list->args[1], 1);
		ft_putstr_fd("\n", 1);
	}
}

void	unset(t_data *shell, char *var)
{
	char	**new_envp;
	int		size;
	int		i;
	int		j;

	i = 0;
	j = 0;
	size = 0;
	while (shell->envp[size])
		size++;
	while (shell->envp[i])
	{
		if (!ft_strncmp(var, shell->envp[i], ft_strlen(var)))
		{
			printf("\n\n\n found envvar %i \n\n\n", i);
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
			shell->envp = new_envp;
			break ;
		}
		i++;
	}
}

// void	export(t_data *shell)
// {
	
// }

void	ft_exit(t_data *shell)
{
	free_all(shell);
	exit(0);
}

/*
◦ export with no options - neue vriable ins env speichern, alphabetische reihenfolge beachten, wird in bash in subshell ausgeführt
◦ unset with no options - löscht variable aus env, wird in bash in subshell ausgeführt
*/
