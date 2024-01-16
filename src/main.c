/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 14:33:44 by mottjes           #+#    #+#             */
/*   Updated: 2024/01/16 12:42:00 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char *input;
	t_token *token;

	while (1)
	{
		get_promt(&input);
		lexer(&input, &token);

		while (token)
		{
			printf("token pos: %i\n", token->pos);
			printf("token str: %s\n", token->str);
			printf("token type: %u\n", token->type);
			token = token->next;
		}
	}
}
































/*

// void	lexer(char *input)
// {
// 	t_lexer *start;
// 	t_lexer *next;
// 	int i;
	
// 	i = 0;
// 	while (input)
// 	{
// 		start = malloc(sizeof(t_lexer));
// 		start->pos = i;
// 		start->next = next;
// 	}
	
// }

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
	char *input;
	pid_t pid;
	int status;
	char *argv[] = {"/bin/ls", NULL};
	
	while (1)
	{
		input = get_promt(&input);

		//lexer(input);
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
*/