/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 14:33:44 by mottjes           #+#    #+#             */
/*   Updated: 2024/01/18 14:37:38 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void print_lexer(t_token *token)
{
	while(token)
	{
		printf("pos: %d\n", token->pos);
		printf("str: %s\n", token->str);
		printf("type: %d\n", token->type);
		token = token->next;
	}
}

// void	tokens_free(t_token **token_ptr)
// {
// 	t_token *next;
// 	t_token	*current;

// 	current = *token_ptr;
// 	while (current)
// 	{
// 		next = current->next;
// 		free(current->str);
// 		free (current);
// 		current = next;
// 	}
// 	*token_ptr = NULL;
// }



int	main(void)
{
	char *input;
	t_token 	*token;

	token = NULL;
	while (1)
	{
		signals();
		get_promt(&input);
		lexer(&input, &token);
		free(input);
		//parser();

		
		print_lexer(token);
		//tokens_free(&token);
	}
}




/*
readline functions:
readline, -> reads line puts promt
rl_clear_history, -> clears input history
rl_on_new_line,	-> Tell the update functions that we have moved onto a new (empty) line, usually after outputting a newline.
rl_replace_line, -> Replace the contents of rl_line_buffer with text. The point and mark are preserved, if possible. If clear_undo is non-zero, the undo list associated with the current line is cleared.
rl_redisplay, -> Change what’s displayed on the screen to reflect the current contents of rl_line_buffer.
add_history, ->adds history
*/
/*
ctrl-C displays a new prompt on a new line. (SIGINT)
◦ ctrl-D exits the shell.
◦ ctrl-\ does nothing

signal,
sigaction, sigemptyset, sigaddset, kill, exit
*/



















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