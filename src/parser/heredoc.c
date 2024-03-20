/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:08:42 by mottjes           #+#    #+#             */
/*   Updated: 2024/03/20 13:23:24 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	read_line(t_token *token, int fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			return ;
		if (!ft_strncmp(line, token->next->str,
				ft_strlen(token->next->str)))
			return ;
		ft_putendl_fd(line, fd);
		free(line);
	}
}

static int	count_heredocs(t_token *token)
{
	int	count;

	count = 0;
	while (token)
	{
		if (token->type == HERE_DOC)
			count++;
		token = token->next;
	}
	return (count);
}

void	unset_heredoc(t_token *token, t_cmd *cmd)
{
	while (token && token->type != PIPE)
	{
		if (token->type == HERE_DOC)
			return ;
		else
			token = token->next;
	}
	cmd->fd_in = 0;
	return ;
}

void	capture_heredoc(t_data *shell, t_token *token, t_cmd *cmd)
{
	int	fd[2];
	int	count;

	count = count_heredocs(shell->token_lst);
	while (count)
	{
		if (pipe(fd) == -1)
			pipe_fail(shell);
		while (token)
		{
			if (token->type == PIPE)
				cmd = cmd->next;
			cmd->fd_in = fd[0];
			if (token->type == HERE_DOC)
			{
				read_line(token, fd[1]);
				token = token->next;
				break ;
			}
			else
				token = token->next;
		}
		close(fd[1]);
		count--;
	}
}
