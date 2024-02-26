/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:14:28 by mottjes           #+#    #+#             */
/*   Updated: 2024/02/26 15:15:10 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	env(char *envp[])
{
	// prints only when variable has value ( = )
	char *env_variable;
	int i;

	i = 0;
	env_variable = envp[i];
	while(env_variable)
	{	
		printf("%s\n", env_variable);
		i++;
		env_variable = envp[i];
	}
}