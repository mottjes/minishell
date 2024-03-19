/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:16:10 by mottjes           #+#    #+#             */
/*   Updated: 2024/03/19 15:24:33 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	skip_quotes(char *str, int i)
{
	if (str[i] == '\'')
	{
		i++;
		while (str[i] && str[i] != '\'')
			i++;
		if (str[i] == '\'')
			i++;
	}
	else if (str[i] == '\"')
	{
		i++;
		while (str[i] && str[i] != '\"')
			i++;
		if (str[i] == '\"')
			i++;
	}
	return (i);
}

void	add_exit_status(t_data *shell, int i)
{
	char	*new_str;
	char	*nbr_str;
	int		nbr_len;
	int		str_len;

	if (shell->exit_status > 255)
		shell->exit_status = shell->exit_status % 255;
	nbr_str = ft_itoa(shell->exit_status);
	nbr_len = ft_strlen(nbr_str);
	str_len = ft_strlen(shell->input);
	new_str = safe_malloc(sizeof(char) * (str_len + nbr_len) + 1, shell);
	ft_strlcpy(new_str, shell->input, i + 1);
	ft_strlcpy(new_str + i, nbr_str, nbr_len + 1);
	ft_strlcpy(new_str + i + nbr_len, shell->input + i + 2,
		str_len - i - nbr_len + 1);
	free(shell->input);
	shell->input = new_str;
}

void	add_space(t_data *shell, int i)
{
	char	*new_input;
	int		size;

	size = ft_strlen(shell->input) + 2;
	new_input = safe_malloc(sizeof(char) * size, shell);
	ft_strlcpy(new_input, shell->input, i + 1);
	new_input[i] = ' ';
	ft_strlcpy(new_input + i + 1, shell->input + i, size - i);
	free(shell->input);
	shell->input = new_input;
}

int	check_after_operator(t_data *shell, int i)
{
	if (shell->input[i + 1] != ' ' && shell->input[i + 1])
	{
		add_space(shell, i + 1);
		return (1);
	}
	return (0);
}

int	check_before_operator(t_data *shell, int i)
{
	if (shell->input[i - 1] != ' ' && shell->input[i - 1])
	{
		add_space(shell, i);
		return (1);
	}
	return (0);
}
