/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:33:53 by mottjes           #+#    #+#             */
/*   Updated: 2024/03/11 16:24:16 by mottjes          ###   ########.fr       */
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

void	exit_status_copy(t_data *shell, int i)
{
	char	*str_mod;
	char	*nbr;
	int		nbr_len;
	int		len;

	if (shell->exit_status > 255)
		shell->exit_status = shell->exit_status - 255;
	nbr = ft_itoa(shell->exit_status);
	nbr_len = ft_strlen(nbr);
	len = ft_strlen(shell->input);
	str_mod = malloc(sizeof(char) * (len + nbr_len + 1));
	if (!str_mod)
		malloc_fail(shell);
	ft_strlcpy(str_mod, shell->input, i + 1);
	ft_strlcpy(str_mod + i, nbr, nbr_len + 1);
	ft_strlcpy(str_mod + i + nbr_len, shell->input + i + 2,
		len - i - nbr_len + 1);
	free(shell->input);
	shell->input = str_mod;
}

void	expansion_exit_status(t_data *shell)
{
	int		i;

	i = 0;
	while (shell->input[i])
	{
		if (shell->input[i] == '\'')
		{
			i++;
			while (shell->input[i] != '\'')
				i++;
			if (shell->input[i] == '\'')
				i++;
		}
		if (shell->input[i] == '$' && shell->input[i + 1] == '?')
			exit_status_copy(shell, i);
		i++;
	}
}
