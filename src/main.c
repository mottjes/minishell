/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 14:33:44 by mottjes           #+#    #+#             */
/*   Updated: 2024/01/22 14:44:41 by mottjes          ###   ########.fr       */
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

int	main(int argc, char *argv[], char *envp[])
{
	t_minishell shell;

	while (1)
	{
		signals();
		get_promt(&shell.input);
		lexer(&shell.input, &shell.token_list);
		parser(shell.token_list, shell.cmd_table);
		
		//print_lexer(shell.token_list);
		//tokens_free(&shell.token_list);
	}
}
