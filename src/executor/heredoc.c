/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbeyer <frbeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:55:15 by mottjes           #+#    #+#             */
/*   Updated: 2024/03/12 17:51:23 by frbeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	has_heredoc(t_data *shell)
{
	t_token	*token;
	t_token	*heredoc;

	heredoc = NULL;
	token = shell->token_list;
	while (token)
	{
		if (token->type == HERE_DOC)
		{
			heredoc = token;
			shell->count_heredoc += 1;
		}
		token = token->next;
	}
	if (heredoc)
	{
		while (heredoc->next)
		{
			heredoc = heredoc->next;
			if (heredoc->type == RE_IN)
				return (0);
		}
		return (1);
	}
	return (0);
}

static void	read_line(t_token *token, int fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!ft_strncmp(line, token->next->str,
				ft_strlen(token->next->str)))
			return ;
		ft_putendl_fd(line, fd);
		free(line);
	}
}

void	capture_heredoc(t_data *shell)
{
	t_token	*token;
	int		fd[2];

	token = shell->token_list;
	while (shell->count_heredoc > 0)
	{
		if (pipe(fd) == -1)
			pipe_fail(shell);
		shell->fd_heredoc = fd[0];
		while (token)
		{
			if (token->type == HERE_DOC)
			{
				read_line(token, fd[1]);
				token = token->next;
				break ;
			}
			else
				token = token->next;
		}
		close (fd[1]);
		shell->count_heredoc--;
	}
	shell->count_heredoc = 0;
}

