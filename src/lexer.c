/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:27:06 by mottjes           #+#    #+#             */
/*   Updated: 2024/01/17 17:17:57 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	tokens_count(char *input)
{
	int i;
	int tokens;

	i = 0;
	tokens = 0;
	while(input[i])
	{
		while(input[i] == ' ' || input[i] == '\t')
			i++;
		if(input[i])
			tokens++;
		while(input[i] != ' ' && input [i] != '\t' && input[i])
			i++;
	}
	return (tokens);
}

void tokens_init(char *input, int count, t_token **token_ptr)
{
	t_token *first_token;
	t_token *next_token;
	int i;

	i = 1;
	first_token = malloc(sizeof(t_token));
	if (!first_token)
		return ; // error handling
	*token_ptr = first_token;
	first_token->pos = i;
	count--;
	while(count)
	{
		next_token = malloc(sizeof(t_token));
		if (!next_token)
			return ; // error handling
		first_token->next = next_token;
		i++;
		next_token->pos = i;
		first_token = next_token;
		count--;
	}
	first_token->next = NULL;
}

void tokens_str_cpy(char *input, t_token **token_ptr)
{
	t_token *token;
	int i;
	int j;
	int size;

	i = 0;
	j = 0;
	size = 0;
	token = *token_ptr;
	while (input[i] && token)
	{
		while (input[i] == ' ' || input[i] == '\t')
			i++;
		j = i;
		while(input[i] != ' ' && input[i] != '\t' && input[i])
		{
			size++;
			i++;
		}
		token->str = malloc(sizeof(char) * size + 1);
		if (!token->str)
			return ; // error handling
		ft_strlcpy(token->str, input + j, size + 1);
		size = 0;
		token = token->next;
	}
}

void	tokens_identify(t_token **token_ptr)
{
	t_token *token;
	
	token = *token_ptr;
	while (token)
	{
		if(token->str[0] == '<')
		{
			if(token->str[1] == '<')
				token->type = HERE_DOC;
		token->type = RE_IN;
		}
		else if(token->str[0] == '>')
		{
			if(token->str[1] + 1 == '>')
				token->type = RE_APP;
		token->type = RE_OUT;
		}
		else if(token->str[0] == '|')
			token->type = PIPE;
		else
			token->type = WORD;
		token = token->next;
	}
}

void	lexer(char **input_ptr, t_token **token_ptr)
{
	int count;
	
	if (**input_ptr == '\0')
		return ;
	input_split(input_ptr);
	count = tokens_count(*input_ptr);
	tokens_init(*input_ptr, count, token_ptr);
	tokens_str_cpy(*input_ptr, token_ptr);
	tokens_identify(token_ptr);
}
