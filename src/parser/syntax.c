/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 21:08:09 by mottjes           #+#    #+#             */
/*   Updated: 2024/03/14 14:22:33 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	syntax_error(int i, bool *restart)
{
	if (i)
		*restart = true;
	if (i == 1)
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
	else if (i == 2)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
	}
}

void	syntax_commands(t_token *token, bool *restart)
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
	*restart = true;
	return ;
}

void	syntax_redirections(t_token *token, bool *restart)
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
