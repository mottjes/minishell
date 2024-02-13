/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:55:15 by mottjes           #+#    #+#             */
/*   Updated: 2024/02/13 16:35:11 by mottjes          ###   ########.fr       */
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

void	executor(t_data *shell)
{
	pid_t	child_pid1;
	pid_t	child_pid2; 
	int		status;
	int		fds[2];
	t_cmd	*cmds;

	// if (cmds->builtin == 1)
	// 	exec_built_in(shell, cmds);
//fds [pipe anzahl][2]
//dementsprechend viele pipes kreieren
	cmds = shell->cmd_list;
//while(cmds)
	if (pipe(fds) == -1)
		return ; //error // close all pipes
	signals_child();
	child_pid1 = fork();
	if (child_pid1   == -1)
		return ; //error
	if (child_pid1 == 0)
	{
		dup2(fds[1], STDOUT_FILENO);
		//close all fds die dieser aktueller childprocess nicht braucht
		close(fds[0]);
		close(fds[1]);
		execve(cmds->path, cmds->args, shell->envp);
		// if (shell->in_file)
		// {
		// 	input_from_in_file(shell);
		// }
		// if (shell->out_file)
		// {
		// 	output_in_out_file(shell);
		// }
		// close die fds die von diesem childporces benutzt wurden
		 //oder return
	}
	if (cmds->next)
		cmds = cmds->next;
	child_pid2 = fork();
	if (child_pid2 == -1)
		return ; //error
	if (child_pid2 == 0)
	{
		dup2(fds[0], STDIN_FILENO);
		//close all fds die dieser aktueller childprocess nicht braucht
		close(fds[0]);
		close(fds[1]);
		execve(cmds->path, cmds->args, shell->envp);
		// exit(0);
	}
	//danach zum nächsten childprocess
	// cmds = cmds->next;
	close(fds[0]);
	close(fds[1]);
// }
//close evry fd that the parent is not using now
//read stdout vom letzten childprocess 
//print in parent ??
//close die restlichen fds
	waitpid(child_pid1, &status, 0); //für jeden childprocess
	waitpid(child_pid2, &status, 0);
}

//fd[0] - read
//fd[1] - write 