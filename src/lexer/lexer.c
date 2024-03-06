/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:27:06 by mottjes           #+#    #+#             */
/*   Updated: 2024/03/06 16:11:38 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	token_list_init(t_data *shell, int count)
{
	t_token	*first_token;
	t_token	*next_token;
	int		i;

	i = 1;
	first_token = malloc(sizeof(t_token));
	if (!first_token)
		malloc_fail(shell);
	shell->token_list = first_token;
	first_token->pos = i;
	count--;
	while (count)
	{
		next_token = malloc(sizeof(t_token));
		if (!next_token)
			malloc_fail(shell);
		first_token->next = next_token;
		i++;
		next_token->pos = i;
		first_token = next_token;
		count--;
	}
	first_token->next = NULL;
	return ;
}

void	tokens_str_cpy(t_data *shell)
{
	t_token	*token;
	int		i;
	int		size;
	int		j;

	i = 0;
	token = shell->token_list;
	while (shell->input[i] && token)
	{
		while (shell->input[i] == ' ' || shell->input[i] == '\t')
			i++;
		j = i;
		size = get_str_size(shell, i);
		if (shell->input[i] == '\"' || shell->input[i] == '\'')
		{
			i += 2;
			j++;
		}
		i += size;
		token->str = malloc(sizeof(char) * size + 1);
		if (!token->str)
			malloc_fail(shell);
		ft_strlcpy(token->str, shell->input + j, size + 1);
		token = token->next;
	}
}

void	tokens_identify(t_token *token_list)
{
	t_token	*token;

	token = token_list;
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
			if (token->str[1] == '>')
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
	count = tokens_count(shell->input, &shell->restart);
	if (!count || shell->restart)
	{
		shell->restart = 1;
		return ;
	}
	token_list_init(shell, count);
	tokens_str_cpy(shell);
	tokens_identify(shell->token_list);
}
