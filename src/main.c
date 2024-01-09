/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 14:33:44 by mottjes           #+#    #+#             */
/*   Updated: 2024/01/09 13:18:34 by mottjes          ###   ########.fr       */
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



void	lexer(char *input)
{
	t_lexer *start;
	t_lexer *next;
	int i;
	
	i = 0;
	while (input)
	{
		start = malloc(sizeof(t_lexer));
		start->pos = i;
		start->next = next;
	}
	
}


int	main(void)
{
	char *input;
	pid_t pid;
	int status;
	char *argv[] = {"/bin/ls", NULL};
	
	while (1)
	{
		input = get_promt(&input);

		lexer(input);

		
		if (!strcmp(input, "exit"))
		 	break;
		if (!strcmp(input, "pwd"))
			sh_pwd();
		if (!strncmp(input, "echo", 4))
			sh_echo(input + 5);
		if (!strcmp(input, "ls"))
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
