/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:19:45 by mottjes           #+#    #+#             */
/*   Updated: 2024/02/12 18:37:46 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
					ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
					*restart = 1;
					return ;
				}
			}
			else
			{
				ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
				*restart = 1;
				return ;
			}
		}
		token = token->next;
	}
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
			if (token_prev->type == WORD)
			{
				if (token_prev_2->type == PIPE || token_prev_2->type == WORD)
				{
					if (token->next)
					{
						if (token->next->type == WORD)
							return ;
					}
					return ;
				}
				ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
				*restart = 1;
				return ;
			}
			ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
			*restart = 1;
			return ;
		}
		token_prev_2 = token_prev;
		token_prev = token;
		token = token->next;
	}
}