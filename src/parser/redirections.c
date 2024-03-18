/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:42:33 by mottjes           #+#    #+#             */
/*   Updated: 2024/03/18 17:36:03 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	delete_cmds(t_data *shell, t_cmd *cmd)
{
	t_cmd	*cmd_lst;
	t_cmd	*cmd_lst_next;

	cmd_lst = shell->cmd_lst;
	while (cmd_lst != cmd)
	{
		cmd_lst_next = cmd_lst->next;
		free_cmd(cmd_lst);
		cmd_lst = cmd_lst_next;
	}
	cmd_lst_next = cmd_lst->next;
	free_cmd(cmd_lst);
	shell->cmd_lst = cmd_lst_next;
}

static bool check_rights(t_data *shell, t_cmd *cmd)
{
	if (cmd->in_file)
	{
		if (access(cmd->in_file, F_OK) == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd->in_file, 2);
			ft_putstr_fd(": No such file or directory\n", 2);	
			shell->exit_status = 1;
			return (true);
		}
		if (access(cmd->in_file, R_OK) == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd->in_file, 2);
			ft_putstr_fd(": Permission denied\n", 2);
			shell->exit_status = 1;
			return (true);
		}
	}
	if (cmd->out_file)
	{
		if (access(cmd->out_file, F_OK) == -1)
			return (false);
		else if (access(cmd->out_file, W_OK) == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd->out_file, 2);
			ft_putstr_fd(": Permission denied\n", 2);
			shell->exit_status = 1;
			return (true);
		}
	}
	return (false);
}

static void	pipe_cmd(t_data *shell, t_cmd * cmd)
{
	int	fd[2];

	if (cmd->next)
	{
		if (pipe(fd) == -1)
		pipe_fail(shell);
		cmd = cmd->next;
		cmd->fd_in = fd[0];
		close(fd[1]);
	}
	else
		shell->exit_status = 1;
}

void	get_redirections(t_data *shell, t_token * token)
{
	t_cmd *cmd;
	
	cmd = shell->cmd_lst;
	capture_heredoc(shell, token, cmd);
	while (token)
	{
		if (token->type == PIPE)
			cmd = cmd->next;
		if (token->type == RE_IN)
		{
			if (cmd->in_file)
				free(cmd->in_file);
			cmd->in_file = ft_strdup(token->next->str);
			if (!cmd->in_file)
				malloc_fail(shell);
			unset_heredoc(token, cmd);
			if (check_rights(shell, cmd))
			{
				pipe_cmd(shell, cmd);
				delete_cmds(shell, cmd);
				cmd = shell->cmd_lst;
				while (token && token->type != PIPE)
					token = token->next;
			}		
		}
		else if (token->type == RE_OUT || token->type == RE_APP)
		{
			if (cmd->out_file)
				free(cmd->out_file);
			cmd->out_file = ft_strdup(token->next->str);
			if (!cmd->out_file)
				malloc_fail(shell);
			if (token->type == RE_APP)
			{
				cmd->out_app = true;
				cmd->fd_out = open(cmd->out_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			}
			else
			{
				cmd->out_app = false;
				cmd->fd_out = open(cmd->out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			}
			if (check_rights(shell, cmd))
			{
				pipe_cmd(shell, cmd);
				delete_cmds(shell, cmd);
				cmd = shell->cmd_lst;
				while (token && token->type != PIPE)
					token = token->next;
			}
		}
		if (token)
			token = token->next;
	}
}
