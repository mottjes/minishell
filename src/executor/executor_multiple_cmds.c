/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_multiple_cmds.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbeyer <frbeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:55:15 by mottjes           #+#    #+#             */
/*   Updated: 2024/03/11 17:30:07 by frbeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_multiple_cmds(t_data *shell, t_cmd *cmds)
{
	int	input_fd;
	int	next_input_fd;
	int	output_fd;
	int	i = 0;
	int	fd[2];
	pid_t	child_pid;

	if (check_rights(shell))
		return ;
	if (shell->in_file != (void *)0 && i == 0)
		input_fd = open(shell->in_file, O_RDONLY, 0644);
	else
		input_fd = STDIN_FILENO;
	if (has_heredoc(shell))
		input_fd = shell->fd_heredoc;
	while (i < shell->cmd_count)
	{
		if (i < shell->cmd_count - 1)
		{
			if (pipe(fd) == -1)
				pipe_fail(shell);
			next_input_fd = fd[0];
			output_fd = fd[1];
		}
		else
		{
			if (shell->out_file != (void *)0)
			{
				output_fd = re_output(shell);
				if (output_fd == -1)
					return ;
			}
			else
				output_fd = STDOUT_FILENO;
		}
		child_pid = fork();
		if (child_pid == -1)
			child_fail(shell);
		if (child_pid == 0)
		{
			if (cmds->builtin == 1)
			{
				if (i == shell->cmd_count - 1)
				{
					shell->fd_built_in = 1;
					if (shell->out_file != (void *)0)
						shell->fd_built_in = re_output(shell);
				}
				else
					shell->fd_built_in = fd[1];
				exec_built_in(shell, cmds);
				next_input_fd = shell->fd_built_in;
			}
			if (dup2(output_fd, STDOUT_FILENO) >= 0
				&& dup2(input_fd, STDIN_FILENO) >= 0)
				execve(cmds->path, cmds->args, shell->envp);
			exit(1);
		}
		cmds->pid = child_pid;
		if (cmds->next)
			cmds = cmds->next;
		i++;
		if (input_fd != STDIN_FILENO)
			close(input_fd);
		if (output_fd != STDOUT_FILENO)
			close(output_fd);
		input_fd = next_input_fd;
	}
}
