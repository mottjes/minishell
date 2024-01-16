/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 14:33:44 by mottjes           #+#    #+#             */
/*   Updated: 2024/01/16 16:02:46 by mottjes          ###   ########.fr       */
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

void	tokens_free(t_token **token_ptr)
{
	t_token *next;
	t_token	*current;

	current = *token_ptr;
	while (current)
	{
		next = current->next;
		free(current->str);
		free (current);
		current = next;
	}
	*token_ptr = NULL;
}

void	add_space(char **input_ptr, int i)
{
	int		size;
	char	*input;
	
	size = ft_strlen(*input_ptr) + 2;
	input = malloc(sizeof(char) * size);
	if (!input)
		return ; //error handling
	ft_strlcpy(input, *input_ptr, i + 1);
	input[i] = ' ';
	ft_strlcpy(input + i + 1, *input_ptr + i, size - i);
	free(*input_ptr);
	*input_ptr = input;
}

void	input_split(char **input_ptr)
{
	int i;
	char *input;

	i = 0;
	input = *input_ptr;
	while(input[i])
	{
		if(input[i] == '<')
		{
			i++;
			if(input[i] == '<')
				i++;
			if (!(input[i] == ' ') && input[i])
				add_space(input_ptr, i);
		}
		else if(input[i] == '>')
		{
			i++;
			if(input[i] == '>')
				i++;
			if (!(input[i] == ' ') && input[i])
				add_space(input_ptr, i);
		}
		i++;
	}
}

int	main(void)
{
	char *input;
	t_token *token;

	while (1)
	{
		get_promt(&input);
		input_split(&input);
		lexer(&input, &token);
		print_lexer(token);
		


		//tokens_free(&token);
		//free(input);
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