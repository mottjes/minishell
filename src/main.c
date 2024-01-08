/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 14:33:44 by mottjes           #+#    #+#             */
/*   Updated: 2024/01/08 17:32:40 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void sh_pwd(void)
{
	char buff[100];
	if (getcwd(buff, 100) == NULL)
		perror("getcwd failed!\n");
	printf("%s\n", buff);
}

void sh_echo(char *arg)
{
	printf("%s\n", arg);
}

void	get_promt(char *promt)
{
	if (getcwd(promt, 100) == NULL)
		perror("getcwd failed!\n");
	strcat(promt, " \% ");
}

int	main(void)
{
	char promt[100];
	char *line;
	pid_t pid;
	int status;
	char *argv[] = {"/bin/ls", NULL};
	
	while (1)
	{
		get_promt(promt);
		line = readline(promt);
		if (!strcmp(line, "exit"))
		 	break;
		if (!strcmp(line, "pwd"))
			sh_pwd();
		if (!strncmp(line, "echo", 4))
			sh_echo(line + 5);
		if (!strcmp(line, "ls"))
		{
			pid = fork();
			if (pid == -1)
				return (printf("Error with fork!"));
			if (pid == 0)
			{
				status = execve(argv[0], argv, NULL);				
				if (status == -1)
					perror("Error(execve)!");
			}
			else
				wait(NULL);
		}
	}
	return (0);
}
