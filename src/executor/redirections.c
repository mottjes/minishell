/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbeyer <frbeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:02:31 by frbeyer           #+#    #+#             */
/*   Updated: 2024/03/06 16:42:37 by frbeyer          ###   ########.fr       */
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
		return (1); //error
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