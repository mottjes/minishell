/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_multiple_cmds.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbeyer <frbeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:55:15 by mottjes           #+#    #+#             */
/*   Updated: 2024/03/19 15:56:31 by frbeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	set_output(t_data *shell, t_cmd *cmds, int i, int fd)
{
	int	output_fd;

	if (i < shell->cmd_count - 1)
		output_fd = fd;
	if (cmds->out_file != 0)
		output_fd = re_output(shell, cmds);
	else if (i == shell->cmd_count - 1)
		output_fd = STDOUT_FILENO;
	return (output_fd);
}

static int	fork_child(t_data *shell, t_cmd *cmds, int input_fd, int output_fd)
{
	pid_t	child_pid;
	int		next_input_fd;

	next_input_fd = 1;
	child_pid = fork();
	if (child_pid == -1)
		child_fail(shell);
	if (child_pid == 0)
	{
		if (cmds->builtin == 1)
		{
			cmds->fd_out = output_fd;
			exec_built_in(shell, cmds);
			next_input_fd = cmds->fd_out;
		}
		if (dup2(output_fd, STDOUT_FILENO) >= 0
			&& dup2(input_fd, STDIN_FILENO) >= 0)
			execve(cmds->path, cmds->args, shell->envp);
		exit(0);
	}
	cmds->pid = child_pid;
	return (next_input_fd);
}

static void	close_fds(int input_fd, int output_fd)
{
	if (input_fd != STDIN_FILENO)
		close(input_fd);
	if (output_fd != STDOUT_FILENO)
		close(output_fd);
}

static void	pipe_cmd(t_data *shell, t_cmd *cmds, int i, int input_fd)
{
	int		fd[2];
	int		output_fd;
	int		next_input_fd;

	while (i < shell->cmd_count)
	{
		if (i < shell->cmd_count - 1)
		{
			if (pipe(fd) == -1)
				pipe_fail(shell);
		}
		output_fd = set_output(shell, cmds, i, fd[1]);
		next_input_fd = fork_child(shell, cmds, input_fd, output_fd);
		if (i < shell->cmd_count - 1)
			next_input_fd = fd[0];
		if (cmds->next)
			cmds = cmds->next;
		if (cmds->in_file != (void *)0)
			next_input_fd = open(cmds->in_file, O_RDONLY, 0644);
		close_fds(input_fd, output_fd);
		input_fd = next_input_fd;
		i++;
	}
}

void	execute_multiple_cmds(t_data *shell, t_cmd *cmds)
{
	int	input_fd;
	int	i;

	i = 0;
	if (cmds->in_file != (void *)0 && i == 0)
		input_fd = open(cmds->in_file, O_RDONLY, 0644);
	else
		input_fd = STDIN_FILENO;
	pipe_cmd(shell, cmds, i, input_fd);
}
