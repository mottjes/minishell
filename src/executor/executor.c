/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:55:15 by mottjes           #+#    #+#             */
/*   Updated: 2024/03/04 17:00:23 by mottjes          ###   ########.fr       */
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

static void	execute_one_cmd(t_data *shell, t_cmd *cmds, pid_t child_pid)
{
	t_token	*token;
	int	i = 0;
	int fdin;
	int fdout;
	int	flag = 0;

	token = shell->token_list;
	if (child_pid == -1)
		return ; //error
	if (child_pid == 0)
	{
		if (shell->in_file != (void *)0 && i == 0)
		{
			fdin = open(shell->in_file, O_RDONLY, 0644);
			dup2(fdin, STDIN_FILENO);
			close(fdin);
		}
		if (shell->out_file != (void *)0)
		{
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
				// printf("macht append\n");
				fdout = open(shell->out_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
				dup2(fdout, STDOUT_FILENO);
				close(fdout);
			}
			else
			{
				// printf("macht kein append\n");
				fdout = open(shell->out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				dup2(fdout, STDOUT_FILENO);
				close(fdout);
			}
		}
		shell->exit_status = 0;
		execve(cmds->path, cmds->args, shell->envp);
	}
}

static void	execute_more_cmds(t_data *shell, t_cmd *cmds, int cmd_count, pid_t child_pid)
{
	int input_fd;
	int next_input_fd;
	int output_fd;
	int	i = 0;
	t_token	*token;
	int fd[2];
	int	flag = 0;

	token = shell->token_list;
	if (shell->in_file != (void *)0 && i == 0)
		input_fd = open(shell->in_file, O_RDONLY, 0644);
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
			{
				while(token->next)
				{
					if (token->type == 4)
						flag = 1;
					if (token->type == 3)
						flag = 0;
					token = token->next;
				}
				if (flag == 1)
					output_fd = open(shell->out_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
				else
					output_fd = open(shell->out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
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
	// signals_child();
	if (cmd_count == 1)
	{
		if (cmds->builtin == 1)
			exec_built_in(shell, cmds);
		else
		{
			child_pid = fork();
			execute_one_cmd(shell, cmds, child_pid);
			waitpid(child_pid, &status, 0);
		}
	}
	if (cmd_count > 1)
	{
		if (cmds->builtin == 1)
			exec_built_in(shell, cmds);
		else
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
