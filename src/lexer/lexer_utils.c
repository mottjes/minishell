/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 19:53:41 by mottjes           #+#    #+#             */
/*   Updated: 2024/03/14 18:15:37 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	tokens_count(char *input, bool *restart)
{
	int	count;
	int	i;
	int	tmp;

	i = 0;
	count = 0;
	while (input[i])
	{
		while (input[i] && (input[i] == ' ' || input[i] == '\t'))
			i++;
		if (!input[i])
			return (count);
		while (input[i] && input[i] != ' ' && input[i] != '\t')
		{
			if (input[i] == '\'' || input[i] == '\"')
			{
				tmp = i;
				i = skip_quotes(input, i);
				if (tmp == i - 2)
					count--;
				if (input[i] == '\0' && input[i - 1] != '\'' && input[i - 1] != '\"')
					return (ft_putstr_fd("minishell: quotes not closed\n", 2), *restart = true, 0);
			}
			else if (input[i])
				i++;
		}
		count++;
	}
	if (count == -1)
		count = 0;
	return (count);
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

int	get_str_size(t_data *shell, int i)
{
	int size;
	int	tmp;

	size = 0;
	while (shell->input[i] && shell->input[i] != ' ' && shell->input[i] != '\t')
	{
		if (shell->input[i] == '\"' || shell->input[i] == '\'')
		{
			tmp = i;
			i = skip_quotes(shell->input, i);
			size += (i - tmp - 2);
		}
		else
		{
			size++;
			i++;
		}
	}
	return (size);
}
