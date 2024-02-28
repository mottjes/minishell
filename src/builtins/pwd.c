/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:14:22 by mottjes           #+#    #+#             */
/*   Updated: 2024/02/28 16:36:57 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pwd(t_data *shell)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		malloc_fail(shell);
	printf("%s\n", cwd);
	free(cwd);
}
