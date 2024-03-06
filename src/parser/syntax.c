/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:19:45 by mottjes           #+#    #+#             */
/*   Updated: 2024/03/06 16:23:34 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	syntax_error(int i, int *restart)
{
	if (i)
		*restart = 1;
	if (i == 1)
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
	else if (i == 2)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
	}
}

void	syntax_commands(t_token *token, int *restart)
{
	t_token	*token_prev;

	token_prev = token;
	while (token)
	{
		if (token->type == WORD)
		{
			if (token_prev->type == WORD || token_prev->type == PIPE)
				return ;
		}
		token_prev = token;
		token = token->next;
	}
	*restart = 1;
	return ;
}

void	syntax_redirections(t_token *token, int *restart)
{
	while (token)
	{
		if (token->type == RE_IN || token->type == HERE_DOC
			|| token->type == RE_OUT || token->type == RE_APP)
		{
			if (token->next)
			{
				if (token->next->type != WORD)
				{
					syntax_error(1, restart);
					return ;
				}
			}
			else
			{
				syntax_error(2, restart);
				return ;
			}
		}
		token = token->next;
	}
}

void	check_before(t_token *token_prev_2, t_token *token, int *restart)
{
	if (token_prev_2->type == PIPE || token_prev_2->type == WORD)
	{
		if (token->next)
		{
			if (token->next->type == WORD)
				return ;
			syntax_error(1, restart);
		}
		return ;
	}
	syntax_error(1, restart);
	return ;
}

void	syntax_pipe(t_token *token, int *restart)
{
	t_token	*token_prev;
	t_token	*token_prev_2;

	token_prev = token;
	token_prev_2 = token_prev;
	while (token)
	{
		if (token->type == PIPE)
		{
			if (!token->next || token->next->type != WORD)
				return (syntax_error(2, restart));
			if (token_prev->type == WORD)
			{
				check_before(token_prev_2, token, restart);
				return ;
			}
			syntax_error(1, restart);
			return ;
		}
		token_prev_2 = token_prev;
		token_prev = token;
		token = token->next;
	}
}
