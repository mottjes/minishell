/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:02:31 by frbeyer           #+#    #+#             */
/*   Updated: 2024/03/13 16:01:23 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	re_output(t_data *shell, t_cmd *cmds)
{
	t_token	*token;
	int		flag;
	int		fd;

	flag = 0;
	token = shell->token_list;
	while (token->next)
	{
		if (token->type == 4)
			flag = 1;
		if (token->type == 3)
			flag = 0;
		token = token->next;
	}
	if (flag == 1)
		fd = open(cmds->out_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(cmds->out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return (fd);
}

int	count_cmds(t_data *shell)
{
	t_cmd	*cmds;
	int		count;

	count = 0;
	cmds = shell->cmd_list;
	while (cmds)
	{
		count++;
		cmds = cmds->next;
	}
	return (count);
}

int	check_rights(t_data *shell, t_cmd *cmds)
{
	static int flag;

	if (cmds->in_file != (void *)0)
	{
		if (access(cmds->in_file, F_OK) == -1)
		{
			if (flag == 0)
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(cmds->in_file, 2);
				ft_putstr_fd(": No such file or directory\n", 2);
				flag = 1;
			}
			shell->exit_status = 1;
			return (1);
		}
		if (access(cmds->in_file, R_OK) == -1)
		{
			if (flag == 0)
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(cmds->in_file, 2);
				ft_putstr_fd(": Permission denied\n", 2);
				flag = 1;
			}
			shell->exit_status = 1;
			return (1);
		}
	}
	if (cmds->out_file != (void *)0)
	{
		if (access(cmds->out_file, F_OK) == -1)
			return (0);
		else if (access(cmds->out_file, W_OK) == -1)
		{
			if (flag == 0)
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(cmds->out_file, 2);
				ft_putstr_fd(": Permission denied\n", 2);
				flag = 1;
			}
			shell->exit_status = 1;
			return (1);
		}
	}
	return (0);
}

// < test_output.txt wc -l >> test_output2.txt 