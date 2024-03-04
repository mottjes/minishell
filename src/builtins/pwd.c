/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:14:22 by mottjes           #+#    #+#             */
/*   Updated: 2024/03/04 15:22:15 by mottjes          ###   ########.fr       */
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
	shell->exit_status = 0;
}
