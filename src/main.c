/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 14:33:44 by mottjes           #+#    #+#             */
/*   Updated: 2024/01/08 14:34:16 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv)
{
	char *line;
	while (1)
	{
		line = readline("minishell %% ");
		
		if(!strcmp(line, "ls"))
			system("ls");
		else if (!strcmp(line, "clear"))
			system("clear");
		else if (!strcmp(line, "exit"))
			break;
	}
	return (0);
}
