/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:55:05 by mottjes           #+#    #+#             */
/*   Updated: 2024/02/05 14:10:57 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_space(char **input_ptr, int i, t_error *error)
{
	int		size;
	char	*input;
	
	size = ft_strlen(*input_ptr) + 2;
	input = malloc(sizeof(char) * size);
	if (!input)
	{
		*error = malloc_failed;
		return ;
	}					
	ft_strlcpy(input, *input_ptr, i + 1);
	input[i] = ' ';
	ft_strlcpy(input + i + 1, *input_ptr + i, size - i);
	free(*input_ptr);
	*input_ptr = input;
}

int	check_before_operator(char **input_ptr, int i, t_error *error)
{
	char *input;

	input = *input_ptr;
	if (input[i - 1] && !(input[i - 1] == ' '))
	{
		add_space(input_ptr, i, error);
		return (1);
	}
	return (0);
}

int	check_after_operator(char **input_ptr, int i, t_error *error)
{
	char	*input;

	input = *input_ptr;
	if (input[i + 1] && !(input[i + 1] == ' '))
	{
		add_space(input_ptr, i + 1, error);
		return (1);
	}
	return (0);
}

void	input_expansion(char **input_ptr, t_error *error)
{
	int i;
	char *input;
	
	i = 0;
	input = *input_ptr;
	while(input[i])
	{
		if(input[i] == '<' && input[i + 1] != '<')
		{
			if (check_before_operator(input_ptr, i, error))
				i++;
		}
		else if(input[i] == '>' && input[i + 1] != '>')
		{
			if (check_before_operator(input_ptr, i, error))
				i++;
		}
		else if(input[i] == '<' && input[i + 1] == '<')
		{
			if (check_before_operator(input_ptr, i, error))
				i++;
			i++;
		}
		else if(input[i] == '>' && input[i + 1] == '>')
		{
			if(check_before_operator(input_ptr, i, error))
				i++;
			i++;
		}
		i++;
		input = *input_ptr;
	}
	i = 0;
	while(input[i])
	{
		if(input[i] == '<' && input[i + 1] != '<')
		{
			if (check_after_operator(input_ptr, i, error))
				i++;
		}
		else if(input[i] == '>' && input[i + 1] != '>')
		{
			if (check_after_operator(input_ptr, i, error))
				i++;
		}
		else if(input[i] == '<' && input[i + 1] == '<')
		{
			if (check_after_operator(input_ptr, i + 1, error))
				i++;
			i++;
		}
		else if(input[i] == '>' && input[i + 1] == '>')
		{
			if (check_after_operator(input_ptr, i + 1, error))
				i++;
			i++;
		}
		i++;
		input = *input_ptr;
	}
}
