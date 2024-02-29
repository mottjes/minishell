/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbeyer <frbeyer@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:55:15 by mottjes           #+#    #+#             */
/*   Updated: 2024/02/28 15:45:43 by frbeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	if (!ft_strncmp(cmd->cmd, "export", 6))
		export(shell, cmd->args[1]);
	if (!ft_strncmp(cmd->cmd, "unset", 3))
		unset(shell, cmd->args[1]);
	else if (!ft_strncmp(cmd->cmd, "env", 5))
		env(shell);
	if (!ft_strncmp(cmd->cmd, "exit", 5))
		ft_exit(shell);
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
	
void	executor(t_data *shell)
{
	t_cmd	*cmds;
	t_token	*token;
	int		cmd_count;
	pid_t	child_pid;
	int		status;

	cmds = shell->cmd_list;
	if (cmds->builtin == 1)
		exec_built_in(shell, cmds);
	cmd_count = count_cmds(shell);
	signals_child();
	token = shell->token_list;
	int	i = 0;
	if (cmd_count == 1)
	{
		child_pid = fork();
		if (child_pid == -1)
			return ; //error
		if (child_pid == 0)
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
					printf("macht append\n");\
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
		waitpid(child_pid, &status, 0);
	}
	if (cmd_count > 1)
	{
		int input_fd;
		int next_input_fd;
		int output_fd;

		if (shell->in_file != (void *)0 && i == 0)
		{
			input_fd = open(shell->in_file, O_RDONLY, 0644);
		}
		else
			input_fd = STDIN_FILENO;
		while(i < cmd_count)
		{
			int fd[2];

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
				{
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
						output_fd = open(shell->out_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
					}
					else
					{
						printf("macht kein append\n");
						output_fd = open(shell->out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
					}
				}
				else
					output_fd = STDOUT_FILENO;
			}
    		child_pid = fork();
    		if (child_pid == 0) 
    		{
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
	cmds = shell->cmd_list;
	while (cmds)
	{
		waitpid(cmds->pid, &status, 0);
		(void)status;
		cmds = cmds->next;
	}
	// free cmds (vielleicht woanders)
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