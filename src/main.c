/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 14:33:44 by mottjes           #+#    #+#             */
/*   Updated: 2024/01/30 11:24:03 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	print_cmds(t_data *shell)
// {
// 	t_cmd *cmds;
// 	int i;

// 	i = 0;
// 	cmds = shell->cmd_list;
// 	while (cmds)
// 	{
// 		if (cmds->cmd)
// 			printf("cmd : %s\n", cmds->cmd);
// 		while (cmds->args[i])
// 		{
// 			printf("arg %i : %s\n", i, cmds->args[i]);
// 			i++;
// 		}
// 		i = 0;
// 		if (cmds->builtin)
// 			printf("builtin : %i\n", cmds->builtin);
// 		if (cmds->path)
// 			printf("path : %s\n", cmds->path);
// 		cmds = cmds->next;
// 	}
	
// }

// void	print_lexer(t_data *shell)
// {
// 	t_token *token;

// 	token = shell->token_list;
// 	while(token)
// 	{
// 		printf("Str: %s\n", token->str);
// 		printf("Pos: %i\n", token->pos);
// 		printf("Type: %i\n", token->type);
// 		token = token->next;
// 	}
// }

int	main(int argc, char *argv[], char *envp[])
{
	t_data shell;

	while (1)
	{
		ft_memset(&shell, 0, sizeof(t_data));
		shell.envp = envp;
		//signals();
		get_promt(&shell);
		lexer(&shell);
		parser(&shell);

		//executor()
	}
	argc = 0;
	argv = NULL;
}

/*
enviromental variables
signal handler
error / free
*/
