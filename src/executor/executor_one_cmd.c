/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_one_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbeyer <frbeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:55:15 by mottjes           #+#    #+#             */
/*   Updated: 2024/03/12 16:22:16 by frbeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_one_cmd(t_data *shell, t_cmd *cmds)
{
	int	fdin;
	int	fdout;

	if (has_heredoc(shell))
	{
		fdin = shell->fd_heredoc;
		dup2(fdin, STDIN_FILENO);
		close(fdin);
	}
	else if (shell->in_file != (void *)0)
	{
		fdin = open(shell->in_file, O_RDONLY, 0644);
		dup2(fdin, STDIN_FILENO);
		close(fdin);
	}
	if (shell->out_file != (void *)0)
	{
		fdout = re_output(shell);
		dup2(fdout, STDOUT_FILENO);
		close(fdout);
	}
	shell->exit_status = 0;
	execve(cmds->path, cmds->args, shell->envp);
}
