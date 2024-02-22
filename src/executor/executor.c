/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbeyer <frbeyer@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:55:15 by mottjes           #+#    #+#             */
/*   Updated: 2024/02/22 18:56:23 by frbeyer          ###   ########.fr       */
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
	
void	executor(t_data *shell)
{
	int		**fds;
	t_cmd	*cmds;
	t_token	*token;
	int		cmd_count;
	pid_t	*child_pid;
	int		status;
	int 	pipe_count = 1;

	// if (cmds->builtin == 1)
	// 	exec_built_in(shell, cmds);
	cmd_count = count_cmds(shell);
	child_pid = create_pid(cmd_count);
	signals_child();
	cmds = shell->cmd_list;
	token = shell->token_list;
	int	i = 0;
	if (cmd_count == 1)
	{
		child_pid[i] = fork();
		if (child_pid[i]   == -1)
			return ; //error
		if (child_pid[i] == 0)
		{
			if (shell->in_file != (void *)0 && i == 0)
			{
				int fdin = open(shell->in_file, O_RDONLY, 0644);
				dup2(fdin, STDIN_FILENO);
				close(fdin);
			}
			if (shell->out_file != (void *)0)
			{				
				int fdout;
				int	flag = 0;
				while(token->next)
				{
					if (token->type == 4)
						flag = 1;
					if (token->type == 3)
						flag = 0;
					token = token->next;
				}
				if (flag == 1)
				{
					printf("macht append\n");
					fdout = open(shell->out_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
					dup2(fdout, STDOUT_FILENO);
					close(fdout);
				}
				else
				{
					printf("macht kein append\n");
					fdout = open(shell->out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
					dup2(fdout, STDOUT_FILENO);
					close(fdout);
				}
			}
			execve(cmds->path, cmds->args, shell->envp);
		}
		waitpid(child_pid[i], &status, 0);
	}
	if (cmd_count > 1)
	{
		fds = create_fds(cmd_count);
		while (pipe_count < cmd_count)
		{
			if (pipe(fds[i]) == -1)
				return ; //error // close all pipes	
			pipe_count++;
		}
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
					if (shell->out_file != (void *)0)
					{
						int fdout;
						int	flag = 0;
						while(token->next)
						{
							if (token->type == 4)
								flag = 1;
							if (token->type == 3)
								flag = 0;
							token = token->next;
						}
						if (flag == 1)
						{
							printf("macht append\n");
							fdout = open(shell->out_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
							dup2(fdout, STDOUT_FILENO);
							close(fdout);
						}
						else
						{
							printf("macht kein append\n");
							fdout = open(shell->out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
							dup2(fdout, STDOUT_FILENO);
							close(fdout);
						}
					}
					execve(cmds->path, cmds->args, shell->envp);
				}
				if (i < cmd_count - 1)
				{
					if (shell->in_file != (void *)0 && i == 0)
					{
						int fdin = open(shell->in_file, O_RDONLY, 0644);
						dup2(fdin, STDIN_FILENO);
						close(fdin);
					}
					dup2(fds[i][1], STDOUT_FILENO);
					close(fds[i][0]);
					close(fds[i][1]);
					execve(cmds->path, cmds->args, shell->envp);
				}
			}
			if (cmds->next)
				cmds = cmds->next;
			i++;
		}
		i = 0;
		while (i < cmd_count - 1)
		{
			close(fds[i][0]);
			close(fds[i][1]);
			i++;
		}
		i = 0;
		while (i < cmd_count)
		{
			waitpid(child_pid[i], &status, 0);
			i++;
		}
		free(child_pid);
		i = 0;
		while (i < cmd_count - 1)
		{
			free(fds[i]);
			i++;
		}
	}
}

// grep "h" test1.txt | wc -l
// < test1.txt cat > test_output.txt > test_output2.txt 
// < test1.txt wc -l | cat > test_output2.txt 
// < test1.txt cat | wc -l >> test_output2.txt
// < test1.txt cat | wc -l >> test_output2.txt > test_output3.txt
// < test1.txt wc -l >> test_output2.txt > test_output3.txt