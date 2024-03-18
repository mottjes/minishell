/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_one_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:55:15 by mottjes           #+#    #+#             */
/*   Updated: 2024/03/18 17:38:46 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_one_cmd(t_data *shell, t_cmd *cmds)
{
	int	fdin;
	int	fdout;

	if (cmds->in_file != (void *)0)
	{
		fdin = open(cmds->in_file, O_RDONLY, 0644);
		dup2(fdin, STDIN_FILENO);
		close(fdin);
	}
	if (cmds->out_file != (void *)0)
	{
		fdout = re_output(shell, cmds);
		dup2(fdout, STDOUT_FILENO);
		close(fdout);
	}
	shell->exit_status = 0;
	if (cmds->fd_in)
	{
		dup2(cmds->fd_in, STDIN_FILENO);
		close(cmds->fd_in);
	}
	execve(cmds->path, cmds->args, shell->envp);
}
