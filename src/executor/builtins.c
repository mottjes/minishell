/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbeyer <frbeyer@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 14:48:01 by mottjes           #+#    #+#             */
/*   Updated: 2024/02/23 20:34:27 by frbeyer          ###   ########.fr       */
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
