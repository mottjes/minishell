/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbeyer <frbeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:55:15 by mottjes           #+#    #+#             */
/*   Updated: 2024/03/11 15:08:40 by frbeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	has_heredoc(t_data *shell)
{
	t_token *token;
	t_token *heredoc;

	
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

void	capture_heredoc(t_data *shell)
{
	t_token *token;
	char	*line;
	int		fd[2];
	int		i = 0;
	
	token = shell->token_list;
	while (i < shell->count_heredoc)
	{
		if (pipe(fd) == -1)
			pipe_fail(shell);
		shell->fd_heredoc = fd[0];	
		while (token)
		{
			if (token->type == HERE_DOC)
			{
				while (1)
				{
					line = readline("> ");
					if (!ft_strncmp(line, token->next->str, ft_strlen(token->next->str)))
						break ;
					ft_putendl_fd(line, fd[1]); // need to overwrite it
					free(line);
				}
				token = token->next;
				break;
			}
			else
				token = token->next;
		}
		close (fd[1]);
		i++;
	}
	shell->count_heredoc = 0;
}
