/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbeyer <frbeyer@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 14:48:01 by mottjes           #+#    #+#             */
/*   Updated: 2024/01/30 14:02:16 by frbeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pwd(void)
{
	char *cwd;
	
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return ;					//errror handling
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

void	cd(char *path)
{
	if (chdir(path))
		return ;									//error handling
}

/*
◦ echo with option -n
◦ cd with only a relative or absolute path
◦ export with no options
◦ unset with no options
◦ exit with no options
*/
