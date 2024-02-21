/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbeyer <frbeyer@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:45:56 by mottjes           #+#    #+#             */
/*   Updated: 2024/02/21 17:57:17 by frbeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*build_promt(t_data *shell, char *cwd)
{
	char	*promt;
	int		size;
	int		i;

	i = 0;
	while (cwd[i])
		i++;
	while (cwd[i - 1] != '/')
		i--;
	size = ft_strlen(cwd + i);
	promt = malloc(sizeof(char) * (size + 9 + 3 + 5));
	if (!promt)
		malloc_fail(shell);
	ft_strlcpy(promt, CYAN BOLD, 10);
	ft_strlcpy(promt + 9, cwd + i, size + 1);
	ft_strlcpy(promt + 9 + size, " % ", 4);
	ft_strlcpy(promt + 9 + size + 3, RESET, 5);
	return (promt);
}

void	input(t_data *shell)
{
	char	*promt;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		malloc_fail(shell);
	promt = build_promt(shell, cwd);
	free(cwd);
	shell->input = readline(promt);
	if (!shell->input)
		shell->restart = 1;
	add_history(shell->input);
	free(promt);
}
