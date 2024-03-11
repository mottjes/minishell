/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbeyer <frbeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:55:15 by mottjes           #+#    #+#             */
/*   Updated: 2024/03/11 14:59:48 by frbeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	executor(t_data *shell)
{
	t_cmd	*cmds;
	int		cmd_count;
	int		status;
	pid_t	child_pid;


	if (shell->restart)
		return ;
	if (has_heredoc(shell))
			capture_heredoc(shell);
	cmds = shell->cmd_list;
	cmd_count = count_cmds(shell);
	signals();
	if (cmd_count == 1)
	{
		if (cmds->builtin == 1)
		{
			shell->fd_built_in = 1;
			if (shell->out_file != (void *)0)
			{
				if (access(shell->out_file, W_OK) == -1)
					return ; //error
				shell->fd_built_in = re_output(shell);
			}
			exec_built_in(shell, cmds); //return(exec_b..);
		}
		else
		{
			child_pid = fork();
			if (child_pid == -1)
				return ; //error
			if (child_pid == 0)
				execute_one_cmd(shell, cmds);
			waitpid(child_pid, &status, 0); ///return(WIFEXit(status))

		}
	}
	if (cmd_count > 1)
	{
		execute_multiple_cmds(shell, cmds, cmd_count, child_pid);
		cmds = shell->cmd_list;
		while (cmds)
		{
			waitpid(cmds->pid, &status, 0);
			(void)status;
			cmds = cmds->next; //return(WIFEXit(status))
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
