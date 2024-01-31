/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 14:33:44 by mottjes           #+#    #+#             */
/*   Updated: 2024/01/31 16:47:16 by mottjes          ###   ########.fr       */
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

void	error_check(t_data *shell)
{
	if (shell->error)
	{
		shell->restart = 1;
		if (shell->error == malloc_failed)
			printf("Error: malloc failed!\n");
		if (shell->error == quotes_not_closed)
			printf("Error: quotes not closed!\n");
		if (shell->error == command_not_found)
			printf("Error: command not found!\n");
	}
}

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
		//parser(&shell);
		//error_check(&shell);
		//executor(&shell);
		//print_cmds(&shell);
		//print_lexer(&shell);
	}
	argc = 0;
	argv = NULL;
}

/*
enviromental variables
signal handler
free
*/
