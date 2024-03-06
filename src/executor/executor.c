/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbeyer <frbeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:55:15 by mottjes           #+#    #+#             */
/*   Updated: 2024/03/06 17:41:34 by frbeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_built_in(t_data *shell, t_cmd *cmd)
{
	if (!ft_strncmp(cmd->cmd, "echo", 4))
		echo(shell, cmd);
	else if (!ft_strncmp(cmd->cmd, "cd", 2))
		cd(shell, cmd);
	else if (!ft_strncmp(cmd->cmd, "pwd", 3))
		pwd(shell);
	else if (!ft_strncmp(cmd->cmd, "export", 6))
		export(shell, cmd);
	else if (!ft_strncmp(cmd->cmd, "unset", 3))
		unset(shell, cmd);
	else if (!ft_strncmp(cmd->cmd, "env", 5))
		env(shell, cmd);
	else if (!ft_strncmp(cmd->cmd, "exit", 5))
		ft_exit(shell, cmd);
}

int		count_cmds(t_data *shell)
{
	t_cmd	*cmds;
	int count = 0;

	cmds = shell->cmd_list;
	while(cmds)
	{
		count++;
		cmds = cmds->next;
	}
	return(count);
}

static void	execute_one_cmd(t_data *shell, t_cmd *cmds)
{
	int fdin;
	int fdout;

	if (cmds->builtin == 1)
	{
		shell->fd_built_in = 1;
		if (shell->out_file != (void *)0)
			shell->fd_built_in = re_output(shell);
		exec_built_in(shell, cmds);
	}
	else
	{
		if (shell->in_file != (void *)0)
		{
			if (access(shell->in_file, R_OK) == -1)
				return ; //error
			fdin = open(shell->in_file, O_RDONLY, 0644);
			dup2(fdin, STDIN_FILENO);
			close(fdin);
		}
		if (shell->out_file != (void *)0)
		{
			if (access(shell->out_file, W_OK) == -1)
				return ; //error
			fdout = re_output(shell);
			dup2(fdout, STDOUT_FILENO);
			close(fdout);
		}
		execve(cmds->path, cmds->args, shell->envp);
	}
	shell->exit_status = 0;
}

static void	execute_more_cmds(t_data *shell, t_cmd *cmds, int cmd_count, pid_t child_pid)
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
				exec_built_in(shell, cmds);
				next_input_fd = shell->fd_built_in;
			}
			// if (access(cmds->path, X_OK) == -1)
			// 	return ; //error
			else if (dup2(output_fd, STDOUT_FILENO) >= 0 && dup2(input_fd, STDIN_FILENO) >= 0)
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

void	executor(t_data *shell)
{
	t_cmd	*cmds;
	int		cmd_count;
	int		status;
	pid_t	child_pid;

	if (shell->restart)
		return ;
	cmds = shell->cmd_list;
	cmd_count = count_cmds(shell);
	// printf("%d\n", cmd_count);
	// signals_child();
	if (cmd_count == 1)
	{
		child_pid = fork();
		if (child_pid == -1)
			return ; //error
		if (child_pid == 0)
			execute_one_cmd(shell, cmds);
		waitpid(child_pid, &status, 0);

	}
	if (cmd_count > 1)
	{
		execute_more_cmds(shell, cmds, cmd_count, child_pid);
		cmds = shell->cmd_list;
		while (cmds)
		{
			waitpid(cmds->pid, &status, 0);
			(void)status;
			cmds = cmds->next;
		}
	}
}

// grep "h" test1.txt | wc -l
// < test1.txt cat | wc -l
// < test1.txt cat > test_output.txt > test_output2.txt 
// < test1.txt wc -l | cat > test_output2.txt 
// < test1.txt cat | wc -l >> test_output2.txt
// < test1.txt cat | wc -l >> test_output2.txt > test_output3.txt
// < test1.txt wc -l >> test_output2.txt > test_output3.txt
// grep "h" test1.txt | grep "a" test1.txt | wc -l
// grep "h" test1.txt | grep "a" test1.txt | grep "s" test1.txt | grep "b" test1.txt
