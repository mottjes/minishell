/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbeyer <frbeyer@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:55:15 by mottjes           #+#    #+#             */
/*   Updated: 2024/02/21 15:28:37 by frbeyer          ###   ########.fr       */
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

void	exec_built_in(t_data *shell, t_cmd *cmd)
{
	if (!ft_strncmp(cmd->cmd, "echo", 4))
	{
		if (!ft_strncmp(cmd->args[0], "-n", 5))
			echo(shell, 1);
		else
			echo(shell, 0);
	}
	else if (!ft_strncmp(cmd->cmd, "cd", 2))
	{
		cd(shell, cmd);
	}
	else if (!ft_strncmp(cmd->cmd, "pwd", 3))
		pwd(shell);
	// if (cmd_list->cmd == "export")
	// 	export(shell);
	// if (cmd_list->cmd == "unset")
	// 	unset(shell);
	else if (!ft_strncmp(cmd->cmd, "env", 5))
		env(shell->envp);
	// if (cmd_list->cmd == "exit")
	// 	exit(shell);
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

int		**create_fds(int cmd_count)
{
	int **ptr;
	int	i = 0;
	
	ptr = malloc(cmd_count * sizeof(int *));
	if (!ptr)
		return (NULL);
	while(i < cmd_count)
	{
		ptr[i] = malloc(2 * sizeof(int));
		if (!ptr[i])
			return (NULL);
		i++;
	}
	return(ptr);
}

pid_t		*create_pid(int cmd_count)
{
	pid_t *ptr;
	
	ptr = malloc(cmd_count * sizeof(pid_t));
	if (!ptr)
		return (NULL);
	return(ptr);
}

// void	dup2_stdout(t_data *shell, t_cmd *cmds, int *fds)
// {
// 	// printf("stdout\n\n");
// 	dup2(fds[1], STDOUT_FILENO);
// 	close(fds[0]);
// 	close(fds[1]);
// 	execve(cmds->path, cmds->args, shell->envp);
// 	exit(0);
// }

// void	dup2_stdin(t_data *shell, t_cmd *cmds, int *fds)
// {
// 	// printf("stdin\n\n");
// 	dup2(fds[0], STDIN_FILENO);
// 	close(fds[0]);
// 	close(fds[1]);
// 	execve(cmds->path, cmds->args, shell->envp);
// 	exit(0);
// }
	
void	executor(t_data *shell)
{
	int		**fds;
	t_cmd	*cmds;
	int		cmd_count;
	pid_t	*child_pid;
	int		status;

	// if (cmds->builtin == 1)
	// 	exec_built_in(shell, cmds);
	cmd_count = count_cmds(shell);
	child_pid = create_pid(cmd_count);
	cmds = shell->cmd_list;
	int	i = 0;
	if (cmd_count == 1)
	{
		child_pid[i] = fork();
		if (child_pid[i]   == -1)
			return ; //error
		if (child_pid[i] == 0)
		{
			execve(cmds->path, cmds->args, shell->envp);
		}
		waitpid(child_pid[i], &status, 0);
	}
	if (cmd_count > 1)
	{
		fds = create_fds(cmd_count);
		int pipe_count = 0;
		while (pipe_count < cmd_count)
		{
			if (pipe(fds[i]) == -1)
				return ; //error // close all pipes	
			pipe_count++;
		}
		// if (pipe(fds[i]) == -1)
		// 	return ; //error // close all pipes	
		// int pipe_count = cmd_count - 1;
		while(i < cmd_count)
		{
			child_pid[i] = fork();
			if (child_pid[i] == -1)
				return ;
			if (child_pid[i] == 0)
			{
				if (i == cmd_count - 1 && i != 0)
				{
					dup2(fds[i-1][0], STDIN_FILENO);
					close(fds[i-1][0]);
					close(fds[i-1][1]);
					execve(cmds->path, cmds->args, shell->envp);
					
				}
				if (i < cmd_count - 1)
				{
					dup2(fds[i][1], STDOUT_FILENO);
					close(fds[i][0]);
					close(fds[i][1]);
					execve(cmds->path, cmds->args, shell->envp);
				}
				// else
				// 	exit(0);
				// printf("cmd = %d\n", *fds[i]);
			}
			// else
			// {
        	// 	close(fds[i][1]);
			// }
			// exit(0);
			if (cmds->next)
				cmds = cmds->next;
			else
				exit(0);
			i++;
		}
		// exit(0);
		i = 0;
		while (i < cmd_count)
		{
			// printf("i2 = %d\n", i);
			close(fds[i][0]);
			close(fds[i][1]);
			i++;
		}
		i = 0;
		while (i < cmd_count)
		{
			// printf("i3 = %d\n", i);
			waitpid(child_pid[i], &status, 0);
			i++;
		}
		free(child_pid);
		i = 0;
		while (i < cmd_count)
		{
			free(fds[i]);
			i++;
		}
		// free(*fds);
	}

	// cmds = shell->cmd_list;
	// if (pipe(fds) == -1)
	// 	return ; //error // close all pipes
	
	// if (cmds->next)
	// 	cmds = cmds->next;
	// child_pid2 = fork();
	// if (child_pid2 == -1)
	// 	return ; //error
	// if (child_pid2 == 0)
	// {
	// 	dup2(fds[0], STDIN_FILENO);
	// 	close(fds[0]);
	// 	close(fds[1]);
	// 	execve(cmds->path, cmds->args, shell->envp);
	// }
}

// grep "h" test1.txt | wc -l