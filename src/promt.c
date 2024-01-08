/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   promt.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:36:17 by mottjes           #+#    #+#             */
/*   Updated: 2024/01/08 17:52:10 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_promt(char **input)
{
	char buff[100];
	int i;

	i = 0;
	if (getcwd(buff, 100) == NULL)
		perror("getcwd failed!\n");

	while (buff[i])
		i++;
	while (buff[i] != '/')
		i--;
	strlcat(buff, " \% ", 100);
	*input = readline(buff + i + 1);
	return (*input);
}
