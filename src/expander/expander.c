/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:55:05 by mottjes           #+#    #+#             */
/*   Updated: 2024/02/13 14:47:33 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_space(char **input_ptr, int i, t_data *shell)
{
	int		size;
	char	*input;

	size = ft_strlen(*input_ptr) + 2;
	input = malloc(sizeof(char) * size);
	if (!input)
		malloc_fail(shell);
	ft_strlcpy(input, *input_ptr, i + 1);
	input[i] = ' ';
	ft_strlcpy(input + i + 1, *input_ptr + i, size - i);
	free(*input_ptr);
	*input_ptr = input;
}

int	check_before_operator(char **input_ptr, int i, t_data *shell)
{
	char	*input;

	input = *input_ptr;
	if (input[i - 1] && !(input[i - 1] == ' '))
	{
		add_space(input_ptr, i, shell);
		return (1);
	}
	return (0);
}

int	check_after_operator(char **input_ptr, int i, t_data *shell)
{
	char	*input;

	input = *input_ptr;
	if (input[i + 1] && !(input[i + 1] == ' '))
	{
		add_space(input_ptr, i + 1, shell);
		return (1);
	}
	return (0);
}

void	expansion_pipe(t_data *shell)
{
	char	**input_ptr;
	int		i;

	i = 0;
	input_ptr = &shell->input;
	while (shell->input[i])
	{
		if (shell->input[i] == '|')
		{
			if (check_before_operator(input_ptr, i, shell))
				i++;
			if (check_after_operator(input_ptr, i, shell))
				i++;
		}
		i++;
	}
}

void	expander(t_data *shell)
{
	char 	**input_ptr;
	char	*input;
	int		i;

	i = 0;
	input_ptr = &shell->input;
	input = *input_ptr;
	if (shell->restart)
		return ;
	expansion_pipe(shell);
	while (input[i])
	{
		if (input[i] == '<' && input[i + 1] != '<')
		{
			if (check_before_operator(input_ptr, i, shell))
				i++;
		}
		else if (input[i] == '>' && input[i + 1] != '>')
		{
			if (check_before_operator(input_ptr, i, shell))
				i++;
		}
		else if (input[i] == '<' && input[i + 1] == '<')
		{
			if (check_before_operator(input_ptr, i, shell))
				i++;
			i++;
		}
		else if (input[i] == '>' && input[i + 1] == '>')
		{
			if (check_before_operator(input_ptr, i, shell))
				i++;
			i++;
		}
		i++;
		input = *input_ptr;
	}
	i = 0;
	while (input[i])
	{
		if (input[i] == '<' && input[i + 1] != '<')
		{
			if (check_after_operator(input_ptr, i, shell))
				i++;
		}
		else if (input[i] == '>' && input[i + 1] != '>')
		{
			if (check_after_operator(input_ptr, i, shell))
				i++;
		}
		else if (input[i] == '<' && input[i + 1] == '<')
		{
			if (check_after_operator(input_ptr, i + 1, shell))
				i++;
			i++;
		}
		else if (input[i] == '>' && input[i + 1] == '>')
		{
			if (check_after_operator(input_ptr, i + 1, shell))
				i++;
			i++;
		}
		i++;
		input = *input_ptr;
	}
}
