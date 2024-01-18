/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:53:35 by mottjes           #+#    #+#             */
/*   Updated: 2024/01/18 16:55:53 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	- reads token list 
	- checks syntax
	- wrong syntax -> error return and restart the loop
	- builds the command table
*/
/*
	syntax rules:
		multiple in and outfiles allowed?????
*/

void	syntax_check(t_token *token)
{
	t_token *token_before;
	
	token_before = NULL;
	while (token)
	{
		if (token->type == RE_IN || token->type == RE_OUT || token->type == RE_APP)
		{
			if (token->next)
			{
				if (token->next->type != WORD)
					printf("Error in Syntax\n");
				return ;									//error handling
			}
			else
			{
				printf("Error in Syntax\n");
				return ;
			}
		}
		if (token->type == PIPE)
		{
			if (!token_before || token_before != WORD || token->next->type != WORD)
			{
				printf("Error in Syntax\n");
				return ;
			}
		}
		token_before = token;
		token = token->next;
	}
}

void	parser(t_token *token)
{
	syntax_check(token);

	//command_table_init();
}
