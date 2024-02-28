/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:33:53 by mottjes           #+#    #+#             */
/*   Updated: 2024/02/28 13:48:13 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_space(t_data *shell, int i)
{
	int		size;
	char	*new_input;

	size = ft_strlen(shell->input) + 2;
	new_input = malloc(sizeof(char) * size);
	if (!new_input)
		malloc_fail(shell);
	ft_strlcpy(new_input, shell->input, i + 1);
	new_input[i] = ' ';
	ft_strlcpy(new_input + i + 1, shell->input + i, size - i);
	free(shell->input);
	shell->input = new_input;
}

int	check_before_operator(t_data *shell, int i)
{
	if (!shell->input)
		return (0);
	if (shell->input[i - 1] && shell->input[i - 1] != ' ')
	{
		add_space(shell, i);
		return (1);
	}
	return (0);
}

int	check_after_operator(t_data *shell, int i)
{
	if (!shell->input)
		return (0);
	if (shell->input[i + 1] && shell->input[i + 1] != ' ')
	{
		add_space(shell, i + 1);
		return (1);
	}
	return (0);
}
