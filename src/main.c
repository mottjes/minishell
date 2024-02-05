/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 14:33:44 by mottjes           #+#    #+#             */
/*   Updated: 2024/02/05 14:16:12 by mottjes          ###   ########.fr       */
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
			ft_putstr_fd("minishell: malloc failed\n", 2);
		if (shell->error == quotes_not_closed)
			ft_putstr_fd("minishell: quotes not closed\n", 2);
		if (shell->error == command_not_found)
			ft_putstr_fd("minishell: command not found\n", 2);
		if (shell->error == env_var_not_found)
			ft_putstr_fd("minishell: environment variable not found\n", 2);
		if (shell->error == syntax_error)
			ft_putstr_fd("minishell: syntax error\n", 2);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data shell;

	(void)argc;
	(void)argv;
	while (1)
	{
		ft_memset(&shell, 0, sizeof(t_data));
		shell.envp = envp;
		//signals();
		input_get(&shell);
		lexer(&shell);
		parser(&shell);
		
		//print_cmds(&shell);
		//executor(&shell);
		//print_lexer(&shell);
	}
}

/*
if malloc fails its high risk to get seg fault -> exit shell

check for read rights in input file
check for write rights in output file
check for execution rights in commands

enviromental variables

signal handler

free/error/quit
*/
