/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:27:06 by mottjes           #+#    #+#             */
/*   Updated: 2024/02/05 17:10:14 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	tokens_count(char *input, t_error *error)
{
	int	tokens;
	int	i;
	int	j;

	j = 0;
	i = 0;
	tokens = 0;
	while (input[i])
	{
		while (input[i] == ' ' || input[i] == '\t')
			i++;
		j = check_for_quotes(input, error, i);
		if (j)
		{
			i += j;
			tokens++;
		}
		else if (input[i])
		{
			tokens++;
			while (input[i] != ' ' && input [i] != '\t' && input[i])
				i++;
		}
	}
	return (tokens);
}

void	token_list_init(int count, t_token **token_ptr, t_error *error)
{
	t_token	*first_token;
	t_token	*next_token;
	int		i;

	i = 1;
	first_token = malloc(sizeof(t_token));
	if (!first_token)
		malloc_fail(error);
	*token_ptr = first_token;
	first_token->pos = i;
	count--;
	while (count)
	{
		next_token = malloc(sizeof(t_token));
		if (!next_token)
			malloc_fail(error);
		first_token->next = next_token;
		i++;
		next_token->pos = i;
		first_token = next_token;
		count--;
	}
	first_token->next = NULL;
	return ;
}

void	tokens_str_cpy(char *input, t_token **token_ptr, t_error *error)
{
	t_token	*token;
	int		size;
	int		i;
	int		j;

	i = 0;
	token = *token_ptr;
	while (input[i] && token)
	{
		while (input[i] == ' ' || input[i] == '\t')
			i++;
		j = i;
		size = check_for_quotes(input, error, i);
		if (size)
			i += size;
		else if (input[i])
			i = get_str_size(input, i, size);
		token->str = malloc(sizeof(char) * size + 1);
		if (!token->str)
			malloc_fail(error);
		ft_strlcpy(token->str, input + j, size + 1);
		token = token->next;
	}
}

void	tokens_identify(t_token **token_ptr)
{
	t_token	*token;

	token = *token_ptr;
	while (token)
	{
		if (token->str[0] == '<')
		{
			if (token->str[1] == '<')
				token->type = HERE_DOC;
			else
				token->type = RE_IN;
		}
		else if (token->str[0] == '>')
		{
			if (token->str[1] + 1 == '>')
				token->type = RE_APP;
			else
				token->type = RE_OUT;
		}
		else if (token->str[0] == '|')
			token->type = PIPE;
		else
			token->type = WORD;
		token = token->next;
	}
}

void	lexer(t_data *shell)
{
	int	count;

	if (shell->restart)
		return ;
	input_expansion(&shell->input, &shell->error);
	count = tokens_count(shell->input, &shell->error);
	if (!count)
	{
		shell->restart = 1;
		return ;
	}
	token_list_init(count, &shell->token_list, &shell->error);
	tokens_str_cpy(shell->input, &shell->token_list, &shell->error);
	tokens_identify(&shell->token_list);
	get_env_vars(shell);
	error_check(shell);
}
