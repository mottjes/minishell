/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:27:06 by mottjes           #+#    #+#             */
/*   Updated: 2024/03/12 16:24:59 by mottjes          ###   ########.fr       */
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
	int		size;
	int		tmp;
	int		i;
	int		j;

	i = 0;
	token = shell->token_list;
	while (shell->input[i] && token)
	{
		j = 0;
		size = 0;
		tmp = i;
		while (shell->input[i] && (shell->input[i] == ' ' || shell->input[i] == '\t'))
			i++;
		while (shell->input[i] && shell->input[i] != ' ' && shell->input[i] != '\t')
		{
			if (shell->input[i] == '\"')
			{
				i++;
				while (shell->input[i] != '\"' && shell->input[i])
				{
						size++;
						i++;
				}
				if (shell->input[i] == '\"')
					i++;
			}
			else if (shell->input[i] == '\'')
			{
				i++;
				while (shell->input[i] != '\'' && shell->input[i])
				{
					size++;
					i++;
				}
				if (shell->input[i] == '\'')
					i++;
			}
			else
			{
				size++;
				i++;
			}
		}
		token->str = malloc(sizeof(char) * size + 1);
		if (!token->str)
			malloc_fail(shell);
		i = tmp;
		if (size == 0)
			token->str[0] = '\0';
		while (shell->input[i] && (shell->input[i] == ' ' || shell->input[i] == '\t'))
			i++;
		while (shell->input[i] && shell->input[i] != ' ' && shell->input[i] != '\t')
		{
			if (shell->input[i] == '\"')
			{
				i++;
				while (shell->input[i] != '\"' && shell->input[i])
				{
					ft_strlcpy(token->str + j, shell->input + i, 2);
					j++;
					i++;
				}
				if (shell->input[i] == '\"')
					i++;
			}
			else if (shell->input[i] == '\'')
			{
				i++;
				while (shell->input[i] != '\'' && shell->input[i])
				{
					ft_strlcpy(token->str + j, shell->input + i, 2);
					j++;
					i++;
				}
				if (shell->input[i] == '\'')
					i++;
			}
			else
			{
				ft_strlcpy(token->str + j, shell->input + i, 2);
				j++;
				i++;
			}
		}
		token = token->next;
	}
}

void	set_token_type(t_data *shell, t_token *token, int i)
{
	if (shell->input[i] == '<')
	{
		if (shell->input[i + 1] == '<')
			token->type = HERE_DOC;
		else
			token->type = RE_IN;
	}
	else if (shell->input[i] == '>')
	{
		if (shell->input[i + 1] == '>')
			token->type = RE_APP;
		else
			token->type = RE_OUT;
	}
	else if (shell->input[i] == '|')
		token->type = PIPE;
	else
		token->type = WORD;
}

void	tokens_identify(t_data *shell)
{
	t_token	*token;
	int	i;
	
	i = 0;
	token = shell->token_list;
	while (shell->input[i] && token)
	{
		while (shell->input[i] && (shell->input[i] == ' ' || shell->input[i] == '\t'))
			i++;
		while (shell->input[i] && shell->input[i] != ' ' && shell->input[i] != '\t')
		{
			if (shell->input[i] == '\"')
			{
				i++;
				token->type = WORD;
				while (shell->input[i] != '\"' && shell->input[i])
					i++;
				if (shell->input[i] == '\"')
					i++;
			}
			else if (shell->input[i] == '\'')
			{
				i++;
				token->type = WORD;
				while (shell->input[i] != '\'' && shell->input[i])
					i++;
				if (shell->input[i] == '\'')
					i++;
			}
			else
			{
				set_token_type(shell, token, i);
				i++;
			}
		}
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
	tokens_identify(shell);
	tokens_str_cpy(shell);
}
