/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:08:02 by mottjes           #+#    #+#             */
/*   Updated: 2024/03/20 15:08:49 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	copy_double_quotes(t_data *shell, t_token *token, int j)
{
	j++;
	while (shell->input[j] != '\"' && shell->input[j])
	{
		ft_strlcpy(token->str + shell->index, shell->input + j, 2);
		j++;
		shell->index++;
	}
	if (shell->input[j] == '\"')
		j++;
	return (j);
}

int	copy_single_quotes(t_data *shell, t_token *token, int j)
{
	j++;
	while (shell->input[j] != '\'' && shell->input[j])
	{
		ft_strlcpy(token->str + shell->index, shell->input + j, 2);
		j++;
		shell->index++;
	}
	if (shell->input[j] == '\'')
		j++;
	return (j);
}
