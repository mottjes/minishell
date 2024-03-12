/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:42:48 by mottjes           #+#    #+#             */
/*   Updated: 2024/03/12 17:10:35 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cmds_count(t_token *token)
{
	int	count;

	count = 1;
	while (token)
	{
		if (token->type == PIPE)
			count++;
		token = token->next;
	}
	return (count);
}

int	arg_count(t_token *token)
{
	int	count;

	count = 1;
	while (token && token->type == WORD)
	{
		while (token->type == RE_IN || token->type == RE_OUT || token->type == RE_APP || token->type == HERE_DOC)
		{
			token = token->next;
			token = token->next;
		}
		token = token->next;
		count++;
	}
	return (count);
}
