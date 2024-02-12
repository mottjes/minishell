/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 14:48:01 by mottjes           #+#    #+#             */
/*   Updated: 2024/02/12 18:05:37 by mottjes          ###   ########.fr       */
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

// void	echo(t_data *shell, int flag)
// {
// 	if (flag == 1)
// 		ft_putstr_fd("%s", shell->cmd_list->args[0]);
// 	if (flag == 0)
// 		ft_putstr_fd("%s\n", shell->cmd_list->args[1]);
// }

/*
◦ echo with option -n
◦ cd with only a relative or absolute path
◦ export with no options
◦ unset with no options
◦ exit with no options
*/
