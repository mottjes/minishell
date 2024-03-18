/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:41:32 by mottjes           #+#    #+#             */
/*   Updated: 2024/03/14 15:59:05 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pwd(t_data *shell, t_cmd *cmd)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		malloc_fail(shell);
	ft_putendl_fd(cwd, cmd->fd_out);
	free(cwd);
	shell->exit_status = 0;
}