/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:27:06 by mottjes           #+#    #+#             */
/*   Updated: 2024/01/16 12:58:12 by mottjes          ###   ########.fr       */
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
		if(input[i] == '<' || input[i] == '>')
		{
			i++;
			if (input[i] == '<' || input[i] == '>')
				i++;
			while(input[i] == ' ' || input[i] == '\t')
				i++;
			tokens++;
		}
		else if(input[i])
			tokens++;
		while(input[i] != ' ' && input [i] != '\t' && input[i])
			i++;
	}
	return (tokens);
}

void tokens_init(char *input, int count, t_token **token)
{
	t_token *first_token;
	t_token *next_token;
	int i;

	i = 1;
	first_token = malloc(sizeof(t_token));
	if (!first_token)
		return ;
	*token = first_token;
	first_token->pos = i;
	count--;
	while(count)
	{
		next_token = malloc(sizeof(t_token));
		if (!next_token)
			return ;
		first_token->next = next_token;
		i++;
		next_token->pos = i;
		first_token = next_token;
		count--;
	}
}


int identify_re_in_and_here_doc(char *input, int i, t_token *token_ptr)
{
	if (input[i] == '<')
	{
		i++;
		if(input[i] == '>')
			return(-1);
		if(input[i] == '<')
		{
			token_ptr->type = HERE_DOC;
			i++;
		}
		else
			token_ptr->type = RE_IN;
		while (input[i] == ' ' || input[i] == '\t')
			i++;
	}
	return (i);
}

int identify_re_out_and_re_app(char *input, int i, t_token *token_ptr)
{
	if(input[i] == '>')
	{
		i++;
		if(input[i] == '<')
			return(-1);
		if(input[i] == '>')
		{
			i++;
			token_ptr->type = RE_APP;
		}
		else
			token_ptr->type = RE_OUT;
		while (input[i] == ' ' || input[i] == '\t')
			i++;
	}
	return (i);
}

int	token_identify(char *input, int i, t_token *token_ptr)
{
	if (identify_re_in_and_here_doc(input, i, token_ptr) == -1)
		return (printf("minishell: syntax error"), -1);
	if (!token_ptr->type)
	{
		if(identify_re_out_and_re_app(input, i, token_ptr) == -1)
			return(printf("minishell: syntax error"), -1);
	}
	if (!token_ptr->type)
	{
		if (input[i] == '|')
		{
			if (input[i + 1] != ' ' && input[i + 1] != '\t')
				return (printf("minishell: syntax error near unexpected token `|'\n"), 1);	
			token_ptr->type = PIPE;
		}
		else 
			token_ptr->type = WORD;
		return (i);
	}
	return (i);
}	

void token_str_cpy(char *input, t_token **token)
{
	t_token *token_ptr;
	int i;
	int j;
	int size;

	i = 0;
	j = 0;
	size = 0;
	token_ptr = *token;
	while (input[i] && token_ptr != NULL)
	{
		while (input[i] == ' ' || input[i] == '\t')
			i++;
		i = token_identify(input, i, token_ptr);
		j = i;
		while(input[i] != ' ' && input[i] != '\t' && input[i])
		{
			size++;
			i++;
		}
		token_ptr->str = malloc(sizeof(char) * size + 1);
		if (!token_ptr->str)
			return ;
		ft_strlcpy(token_ptr->str, input + j, size + 1);
		size = 0;
		token_ptr = token_ptr->next;
	}
}
void	tokens_identify()
{
	
}

void	lexer(char **input, t_token **token)
{
	int count;
	
	if (**input == '\0')
		return ;
	count = tokens_count(*input);
	tokens_init(*input, count, token);
	token_str_cpy(*input, token);
	tokens_identify(*input, count);
}
