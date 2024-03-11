/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbeyer <frbeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:02:31 by frbeyer           #+#    #+#             */
/*   Updated: 2024/03/11 15:39:18 by frbeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	re_output(t_data *shell)
{
	int	flag;
	int fd;
	t_token	*token;
	
	flag = 0;
    token = shell->token_list;
	if (access(shell->out_file, W_OK) == -1)
	{
		ft_putstr_fd("minishell: NO WRITING RIGHTS\n", 2);
		return(-1);
	}
	while(token->next)
	{
		if (token->type == 4)
			flag = 1;
		if (token->type == 3)
			flag = 0;
		token = token->next;
	}
	if (flag == 1)
		fd = open(shell->out_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(shell->out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return (fd);
}

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