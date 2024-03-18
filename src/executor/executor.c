/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:55:15 by mottjes           #+#    #+#             */
/*   Updated: 2024/03/18 17:45:46 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	exec_one(t_data *shell, t_cmd *cmds)
{
	pid_t	child_pid;
	int		status;

	if (cmds->builtin == 1)
	{
		cmds->fd_out = 1;
		if (cmds->out_file != (void *)0)
			cmds->fd_out = re_output(shell, cmds);
		exec_built_in(shell, cmds);
	}
	else
	{
		child_pid = fork();
		if (child_pid == -1)
			child_fail(shell);
		if (child_pid == 0)
			execute_one_cmd(shell, cmds);
		waitpid(child_pid, &status, 0);
		if (cmds->fd_in)
			close(cmds->fd_in);
		shell->exit_status = status;
	}
}

static void	exec_multiple(t_data *shell, t_cmd *cmds)
{
	int	status;

	execute_multiple_cmds(shell, cmds);
	cmds = shell->cmd_lst;
	while (cmds)
	{
		waitpid(cmds->pid, &status, 0);
		shell->exit_status = status;
		(void)status;
		if (cmds->fd_in)
			close(cmds->fd_in);
		cmds = cmds->next;
	}
}

void	executor(t_data *shell)
{
	t_cmd	*cmds;
	int		cmd_count;

	if (shell->restart)
		return ;
	cmds = shell->cmd_lst;
	shell->cmd_count = count_cmds(shell);
	if (shell->cmd_count == 1)
		exec_one(shell, cmds);
	if (shell->cmd_count > 1)
		exec_multiple(shell, cmds);
	shell->cmd_count = 0;
}

// grep "h" test1.txt | wc -l
// < test1.txt cat | wc -l
// < test1.txt cat > test_output.txt > test_output2.txt 
// < test1.txt wc -l | cat > test_output2.txt 
// < test1.txt cat | wc -l >> test_output2.txt
// < test1.txt cat | wc -l >> test_output2.txt > test_output3.txt
// < test1.txt wc -l >> test_output2.txt > test_output3.txt
// grep "h" test1.txt | grep "a" test1.txt | wc -l
// grep "h" test1.txt | grep "a" test1.txt | grep "s" test1.txt
