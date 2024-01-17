/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:55:05 by mottjes           #+#    #+#             */
/*   Updated: 2024/01/17 17:20:37 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_space(char **input_ptr, int i)
{
	int		size;
	char	*input;
	
	size = ft_strlen(*input_ptr) + 2;
	input = malloc(sizeof(char) * size);
	if (!input)
		return ;			//error handling
	ft_strlcpy(input, *input_ptr, i + 1);
	input[i] = ' ';
	ft_strlcpy(input + i + 1, *input_ptr + i, size - i);
	free(*input_ptr);
	*input_ptr = input;
	printf("%s\n", input);
}

int	check_before_operator(char **input_ptr, int i)
{
	char *input;

	input = *input_ptr;
	if (input[i - 1] && !(input[i - 1] == ' '))
	{
		add_space(input_ptr, i);
		return (1);
	}
	return (0);
}

int	check_after_operator(char **input_ptr, int i)
{
	char	*input;

	input = *input_ptr;
	if (input[i + 1] && !(input[i + 1] == ' '))
	{
		add_space(input_ptr, i + 1);
		return (1);
	}
	return (0);
}

void	input_split(char **input_ptr)
{
	int i;
	char *input;
	
	i = 0;
	input = *input_ptr;
	
	i = 0;
	while(input[i])
	{
		if(input[i] == '<' && input[i + 1] != '<')
		{
			if (check_before_operator(input_ptr, i))
				i++;
		}
		else if(input[i] == '>' && input[i + 1] != '>')
		{
			if (check_before_operator(input_ptr, i))
				i++;
		}
		else if(input[i] == '<' && input[i + 1] == '<')
		{
			if (check_before_operator(input_ptr, i))
				i++;
			i++;
		}
		else if(input[i] == '>' && input[i + 1] == '>')
		{
			if(check_before_operator(input_ptr, i))
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
			if (check_after_operator(input_ptr, i))
				i++;
		}
		else if(input[i] == '>' && input[i + 1] != '>')
		{
			if (check_after_operator(input_ptr, i))
					i++;
		}
		else if(input[i] == '<' && input[i + 1] == '<')
		{
			if (check_after_operator(input_ptr, i + 1))
				i++;
			i++;
		}
		else if(input[i] == '>' && input[i + 1] == '>')
		{
			if (check_after_operator(input_ptr, i + 1))
				i++;
			i++;
		}
		i++;
		input = *input_ptr;
	}
}
