/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_redirections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:31:59 by mottjes           #+#    #+#             */
/*   Updated: 2024/03/20 13:21:29 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	expansion_after_redirections(t_data *shell)
{
	int	i;

	i = 0;
	while (shell->input && shell->input[i])
	{
		i = skip_quotes(shell->input, i);
		if ((shell->input[i] == '<' && shell->input[i + 1] != '<')
			|| (shell->input[i] == '>' && shell->input[i + 1] != '>'))
		{
			if (check_after_operator(shell, i))
				i++;
		}
		else if ((shell->input[i] == '<' && shell->input[i + 1] == '<')
			|| (shell->input[i] == '>' && shell->input[i + 1] == '>'))
		{
			if (check_after_operator(shell, i + 1))
				i++;
			i++;
		}
		i++;
	}
}

void	expansion_before_redirections(t_data *shell)
{
	int	i;

	i = 0;
	while (shell->input[i])
	{
		i = skip_quotes(shell->input, i);
		if ((shell->input[i] == '<' && shell->input[i + 1] != '<')
			|| (shell->input[i] == '>' && shell->input[i + 1] != '>'))
		{
			if (check_before_operator(shell, i))
				i++;
		}
		else if ((shell->input[i] == '<' && shell->input[i + 1] == '<')
			|| (shell->input[i] == '>' && shell->input[i + 1] == '>'))
		{
			if (check_before_operator(shell, i))
				i++;
			i++;
		}
		i++;
	}
}
