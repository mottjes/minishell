/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:42:33 by mottjes           #+#    #+#             */
/*   Updated: 2024/03/20 14:36:23 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_error_3(t_data *shell, t_cmd *cmd, int error_nbr)
{
	if (error_nbr == 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->in_file, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		shell->exit_status = 1;
		return ;
	}
	if (error_nbr == 2)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->in_file, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		shell->exit_status = 1;
		return ;
	}
	if (error_nbr == 3)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->out_file, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		shell->exit_status = 1;
		return ;
	}
}

static bool	check_rights(t_data *shell, t_cmd *cmd)
{
	if (cmd->in_file)
	{
		if (access(cmd->in_file, F_OK) == -1)
			return (print_error_3(shell, cmd, 1), true);
		if (access(cmd->in_file, R_OK) == -1)
			return (print_error_3(shell, cmd, 2), true);
	}
	if (cmd->out_file)
	{
		if (access(cmd->out_file, F_OK) == -1)
			return (false);
		else if (access(cmd->out_file, W_OK) == -1)
			return (print_error_3(shell, cmd, 3), true);
	}
	return (false);
}

int	get_in_file(t_data *shell, t_cmd *cmd, t_token *token)
{
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
			return (1);
		}
	}
	return (0);
}

int	get_out_file(t_data *shell, t_cmd *cmd, t_token *token)
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
		return (1);
	}
	return (0);
}

void	get_redirections(t_data *shell, t_token *token)
{
	t_cmd	*cmd;

	cmd = shell->cmd_lst;
	while (token)
	{
		if (token->type == PIPE)
			cmd = cmd->next;
		if (get_in_file(shell, cmd, token))
		{
			cmd = shell->cmd_lst;
			while (token && token->type != PIPE)
				token = token->next;
		}
		else if (token->type == RE_OUT || token->type == RE_APP)
		{
			if (get_out_file(shell, cmd, token))
			{
				cmd = shell->cmd_lst;
				while (token && token->type != PIPE)
					token = token->next;
			}
		}
		if (token)
			token = token->next;
	}
}
