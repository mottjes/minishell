/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mika <mika@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 21:08:09 by mottjes           #+#    #+#             */
/*   Updated: 2024/09/26 17:24:41 by mika             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	syntax_error(t_token *token, bool *restart)
{
	if (!token)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
	}
	else
		*restart = true;
	if (token->type == PIPE)
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
	else if (token->type == RE_IN)
		ft_putstr_fd("minishell: syntax error near unexpected token `<'\n", 2);
	else if (token->type == RE_OUT)
		ft_putstr_fd("minishell: syntax error near unexpected token `>'\n", 2);
	else if (token->type == RE_APP)
		ft_putstr_fd("minishell: syntax error near unexpected token `>>'\n", 2);
	else if (token->type == HERE_DOC)
		ft_putstr_fd("minishell: syntax error near unexpected token `<<'\n", 2);
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
					syntax_error(token->next, restart);
					return ;
				}
			}
			else
			{
				syntax_error(token->next, restart);
				return ;
			}
		}
		token = token->next;
	}
}

void	syntax_pipes(t_token *token, bool *restart)
{
	t_token	*pipe_ptr;
	bool	pipe;

	pipe_ptr = NULL;
	pipe = false;
	while (token)
	{
		if (pipe == true)
		{
			if (token->type == PIPE)
				break ;
			if (token->type == WORD)
				pipe = false;
		}
		if (token->type == PIPE)
		{
			pipe_ptr = token;
			pipe = true;
		}
		token = token->next;
	}
	if (pipe == true)
		syntax_error(pipe_ptr, restart);
	return ;
}
