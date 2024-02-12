/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 14:48:01 by mottjes           #+#    #+#             */
/*   Updated: 2024/02/12 15:33:21 by mottjes          ###   ########.fr       */
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
void	update_old_pwd(t_data *shell)
{
	char	*new_pwd;
	int		size;
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
	i = 0;
	while (shell->envp[i])
	{
		if (!ft_strncmp("OLDPWD=", shell->envp[i], 7))
		{
			free(shell->envp[i]);
			size = ft_strlen(new_pwd);
			shell->envp[i] = malloc(sizeof(char) * (size + 8));
			if (!shell->envp[i])
				malloc_fail(shell);
			ft_strlcpy(shell->envp[i], "OLDPWD=", 8);
			ft_strlcpy(shell->envp[i] + 7, new_pwd, size + 1);
			return ;
		}
		i++;
	}
}
void	update_pwd(t_data *shell)
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
	if (chdir(cmd->args[1]))
		return ;				//error handling
	update_old_pwd(shell);
	update_pwd(shell);
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
