/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbeyer <frbeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:02:31 by frbeyer           #+#    #+#             */
/*   Updated: 2024/03/19 13:44:56 by frbeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	re_output(t_data *shell, t_cmd *cmds)
{
	t_token	*token;
	int		flag;
	int		fd;

	flag = 0;
	token = shell->token_lst;
	while (token->next)
	{
		if (token->type == RE_APP)
			flag = 1;
		if (token->type == RE_OUT)
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
	cmds = shell->cmd_lst;
	while (cmds)
	{
		count++;
		cmds = cmds->next;
	}
	return (count);
}
