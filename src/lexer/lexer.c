/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 19:46:48 by mottjes           #+#    #+#             */
/*   Updated: 2024/03/20 15:08:45 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	token_add_str(t_data *shell, t_token *token, int j)
{
	shell->index = 0;
	while (shell->input[j] && shell->input[j] != ' ' && shell->input[j] != '\t')
	{
		if (shell->input[j] == '\"')
			j = copy_double_quotes(shell, token, j);
		else if (shell->input[j] == '\'')
			j = copy_single_quotes(shell, token, j);
		else
		{
			ft_strlcpy(token->str + shell->index, shell->input + j, 2);
			j++;
			shell->index++;
		}
	}
	shell->index = 0;
	return (j);
}

void	tokens_str_copy(t_data *shell, char *input)
{
	t_token	*token;
	int		size;
	int		i;

	i = 0;
	token = shell->token_lst;
	while (input[i] && token)
	{
		while (input[i] && (input[i] == ' ' || input[i] == '\t'))
			i++;
		if (input[i] == '\'' && input[i + 1] == '\'')
			i += 2;
		else if (input[i] == '\"' && input[i + 1] == '\"')
			i += 2;
		while (input[i] && (input[i] == ' ' || input[i] == '\t'))
			i++;
		size = get_str_size(shell, i);
		token->str = safe_malloc(sizeof(char) * (size + 1), shell);
		if (size == 0)
			token->str[0] = '\0';
		i = token_add_str(shell, token, i);
		token = token->next;
	}
}

void	tokens_identify(t_data *shell, char *input)
{
	t_token	*token;
	int		i;

	i = 0;
	token = shell->token_lst;
	while (input[i] && token)
	{
		while (input[i] && (input[i] == ' ' || input[i] == '\t'))
			i++;
		set_token_type(shell, token, i);
		i = skip_quotes(input, i);
		token = token->next;
		while (shell->input[i] && input[i] != ' ' && input[i] != '\t')
			i++;
	}
}

void	token_lst_init(t_data *shell, int count)
{
	t_token	*first_token;
	t_token	*next_token;
	int		i;

	i = 1;
	first_token = safe_malloc(sizeof(t_token), shell);
	shell->token_lst = first_token;
	first_token->pos = i;
	count--;
	while (count)
	{
		next_token = safe_malloc(sizeof(t_token), shell);
		first_token->next = next_token;
		i++;
		next_token->pos = i;
		first_token = next_token;
		count--;
	}
	first_token->next = NULL;
	return ;
}

void	lexer(t_data *shell)
{
	int	count;

	count = tokens_count(shell->input, &shell->restart, 0, 0);
	if (count == -1)
		count = 0;
	if (!count || shell->restart == true)
	{
		shell->restart = true;
		return ;
	}
	token_lst_init(shell, count);
	tokens_identify(shell, shell->input);
	tokens_str_copy(shell, shell->input);
}
