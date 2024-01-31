/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   promt.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:36:17 by mottjes           #+#    #+#             */
/*   Updated: 2024/01/31 15:09:15 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_promt(t_data *shell)
{
	char	*cwd;
	char	*promt;
	int		len;
	int		i;

	i = 0;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return ;								//errror handling
	while (cwd[i])
		i++;
	while (cwd[i - 1] != '/')
		i--;
	len = ft_strlen(cwd + i);
	promt = malloc(sizeof(char) * (len + 9 + 3 + 5));
	if (!promt)
	{
		free(cwd);
		return ;								//error handling
	}					
	ft_strlcpy(promt, CYAN BOLD, 10);
	ft_strlcpy(promt + 9, cwd + i, len + 1);
	ft_strlcpy(promt + 9 + len, " % ", 4);
	ft_strlcpy(promt + 9 + len + 3, RESET, 5);
	shell->input = readline(promt);
	if (!shell->input)
		shell->restart = 1;
	add_history(shell->input);
	free(cwd);
	free(promt);
}
