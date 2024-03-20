/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbeyer <frbeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:55:15 by mottjes           #+#    #+#             */
/*   Updated: 2024/03/19 15:57:05 by frbeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	exec_one(t_data *shell, t_cmd *cmds)
{
	pid_t	child_pid;
	int		status;

	if (cmds->builtin == 1)
	{
		cmds->fd_out = 1;
		if (cmds->out_file != (void *)0)
			cmds->fd_out = re_output(shell, cmds);
		exec_built_in(shell, cmds);
	}
	else
	{
		child_pid = fork();
		if (child_pid == -1)
			child_fail(shell);
		if (child_pid == 0)
			execute_one_cmd(shell, cmds);
		waitpid(child_pid, &status, 0);
		if (cmds->fd_in)
			close(cmds->fd_in);
		shell->exit_status = status;
	}
}

static void	exec_multiple(t_data *shell, t_cmd *cmds)
{
	int	status;

	execute_multiple_cmds(shell, cmds);
	cmds = shell->cmd_lst;
	while (cmds)
	{
		waitpid(cmds->pid, &status, 0);
		shell->exit_status = status;
		(void)status;
		if (cmds->fd_in)
			close(cmds->fd_in);
		cmds = cmds->next;
	}
}

void	executor(t_data *shell)
{
	t_cmd	*cmds;

	if (shell->restart)
		return ;
	cmds = shell->cmd_lst;
	shell->cmd_count = count_cmds(shell);
	if (shell->cmd_count == 1)
		exec_one(shell, cmds);
	if (shell->cmd_count > 1)
		exec_multiple(shell, cmds);
	shell->cmd_count = 0;
}
