/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:55:15 by mottjes           #+#    #+#             */
/*   Updated: 2024/02/09 13:03:17 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

void	input_from_in_file(t_data *shell)
{
	char	*string;
	int		i;
	int		fd;

	i = 0;
	fd = open(shell->in_file, O_RDONLY);
	if (fd == -1)
	{
		perror("ERROR WITH OPENING FILE");
		return ;
	}
	string = get_next_line(fd);
	while (shell->cmd_list->args[i] != (void *)0)
		i++;
	shell->cmd_list->args[i] = ft_strdup(string);
	free(string);
	close(fd);
}

void	output_in_out_file(t_data *shell)
{
	int fd;

	// close(1);
	fd = open(shell->out_file, O_CREAT | O_WRONLY);
	if (fd == -1)
	{
		perror("ERROR WITH OPENING FILE");
		return ;
	}
	// while ()
	write (fd, "l", 1);
	close(fd);
}

void	exec_built_in(t_data *shell)
{
	t_cmd	*cmd_list;
	t_exec	*exec_list;

	cmd_list = shell->cmd_list;
	exec_list = shell->exec_list;
	if (!ft_strncmp(cmd_list->cmd, "echo", 5))
	{
		if (!ft_strncmp(cmd_list->args[0], "-n", 5))
			echo(shell, 1);
		else
			echo(shell, 0);
	}
	// if (cmd_list->cmd == "cd")
	// 	cd(shell->cmd_list->path);
	if (!ft_strncmp(cmd_list->cmd, "pwd", 5))
		pwd();
	// if (cmd_list->cmd == "export")
	// 	export(shell);
	// if (cmd_list->cmd == "unset")
	// 	unset(shell);
	if (!ft_strncmp(cmd_list->cmd, "env", 5))
		env(shell->envp);
	// if (cmd_list->cmd == "exit")
	// 	exit(shell);
}

void	executor(t_data *shell)
{
	pid_t	child_pid;
	pid_t	wait_pid; //brauchen wir das??
	int		fds[2];

	pipe(fds);
	if (pipe(fds) == -1)
		return ; //error
	child_pid = fork();
	if (child_pid == -1)
		return ; //error
	if (child_pid == 0)
	{
		dup2(fds[0], STDIN_FILENO);
		close(fds[0]);
		close(fds[1]);
		execve(shell->cmd_list->path, shell->cmd_list->args, shell->envp);
		// if (shell->in_file)
		// {
		// 	input_from_in_file(shell);
		// }
		// if (shell->cmd_list->builtin == 1)
		// 	exec_built_in(shell);
        // if (shell->cmd_list->cmd)
		// 	exec_cmd(shell);
		// if (shell->out_file)
		// {
		// 	output_in_out_file(shell);
		// }
		// exit(0);
	}
	int	status;
	wait_pid = waitpid(child_pid, &status, 0);
}

//fd[0] - read
//fd[1] - write