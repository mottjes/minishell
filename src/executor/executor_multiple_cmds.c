/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_multiple_cmds.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbeyer <frbeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:55:15 by mottjes           #+#    #+#             */
/*   Updated: 2024/03/11 14:47:12 by frbeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_multiple_cmds(t_data *shell, t_cmd *cmds, int cmd_count, pid_t child_pid)
{
	int input_fd;
	int next_input_fd;
	int output_fd;
	int	i = 0;
	int fd[2];

	if (shell->in_file != (void *)0 && i == 0)
	{
		if (access(shell->in_file, R_OK) == -1)
			return ; //error
		input_fd = open(shell->in_file, O_RDONLY, 0644);
	}
	else
		input_fd = STDIN_FILENO;
	if (has_heredoc(shell))
		input_fd = shell->fd_heredoc;
	while(i < cmd_count)
	{
		if (i < cmd_count - 1)
		{
			if (pipe(fd) == -1)
				return;
			next_input_fd = fd[0];
			output_fd = fd[1];
		}
		else
		{
			if (shell->out_file != (void *)0)
				output_fd = re_output(shell);
			else
				output_fd = STDOUT_FILENO;
		}
		child_pid = fork();
		if (child_pid == -1)
				return ; //error
		if (child_pid == 0)
		{
			if (cmds->builtin == 1)
			{
				if (i == cmd_count - 1)
				{
					shell->fd_built_in = 1;
					if (shell->out_file != (void *)0)
						shell->fd_built_in = re_output(shell);
				}
				else
					shell->fd_built_in = fd[1];
				exec_built_in(shell, cmds); //exit
				next_input_fd = shell->fd_built_in;
			}
			// if (access(cmds->path, X_OK) == -1)
			// 	return ; //error
			if (dup2(output_fd, STDOUT_FILENO) >= 0 && dup2(input_fd, STDIN_FILENO) >= 0)
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
