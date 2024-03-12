/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:01:25 by mottjes           #+#    #+#             */
/*   Updated: 2024/03/12 16:23:45 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_str_size(t_data *shell, int i)
{
	int	size;

	size = 0;
	if (shell->input[i] == '\"' || shell->input[i] == '\'')
	{
		i++;
		while (shell->input[i] != '\"' && shell->input[i] != '\'')
		{
			i++;
			size++;
		}
	}
	else
	{
		while (shell->input[i] && shell->input[i]
			!= ' ' && shell->input[i] != '\t')
		{
			i++;
			size++;
		}
	}
	return (size);
}

// int	check_for_quotes(char *input, int *restart, int i)
// {
// 	int	j;

// 	j = i;
// 	if (input[i] == '\"')
// 	{
// 		i++;
// 		while (input[i] && input[i] != '\"')
// 			i++;
// 		if (input[i] != '\"')
// 			return (ft_putstr_fd("minishell: quotes not closed\n", 2),
// 				*restart = 1, 0);
// 		i++;
// 	}
// 	else if (input[i] == '\'')
// 	{
// 		i++;
// 		while (input[i] && input[i] != '\'')
// 			i++;
// 		if (input[i] != '\'')
// 			return (ft_putstr_fd("minishell: quotes not closed\n", 2),
// 				*restart = 1, 0);
// 		i++;
// 	}
// 	return (i - j);
// }

int	tokens_count(char *input, int *restart)
{
	int	tokens;
	int	i;

	i = 0;
	tokens = 0;
	while (input[i])
	{
		while (input[i] && (input[i] == ' ' || input[i] == '\t'))
			i++;
		if (!input[i])
			return (tokens);
		while (input[i] && input[i] != ' ' && input[i] != '\t')
		{
			if (input[i] == '\"')
			{
				i++;
				while (input[i] && input[i] != '\"' )
					i++;
				if (input[i] != '\"')
					return (ft_putstr_fd("minishell: quotes not closed\n", 2), *restart = 1, 0);
				else
					i++;
			}
			else if (input[i] == '\'')
			{
				i++;
				while (input[i] && input[i] != '\'')
					i++;
				if (input[i] == '\'')
					i++;
				else
					return (ft_putstr_fd("minishell: quotes not closed\n", 2), *restart = 1, 0);
			}
			else
				i++;
		}
		tokens++;
	}
	return (tokens);
}
