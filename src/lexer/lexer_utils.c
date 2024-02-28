/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:01:25 by mottjes           #+#    #+#             */
/*   Updated: 2024/02/28 11:34:37 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_for_quotes(char *input, int *restart, int i)
{
	int	j;

	j = i;
	if (input[i] == '\"')
	{
		i++;
		while (input[i] && input[i] != '\"')
			i++;
		if (input[i] == '\"')
			i++;
		else
			return (ft_putstr_fd("minishell: quotes not closed\n", 2), *restart = 1, 0);
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
	return (i - j);
}

int	get_str_size(char *input, int i, int size)
{
	while (input[i] != ' ' && input[i] != '\t' && input[i])
	{
		size++;
		i++;
	}
	return (size);
}
