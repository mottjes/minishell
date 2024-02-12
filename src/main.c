/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 14:33:44 by mottjes           #+#    #+#             */
/*   Updated: 2024/02/12 16:44:44 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_cmds(t_data *shell)
{
	t_cmd *cmds;
	int i;

	i = 0;
	cmds = shell->cmd_list;
	while (cmds)
	{
		if (cmds->cmd)
			printf("cmd : %s\n", cmds->cmd);
		while (cmds->args[i])
		{
			printf("arg %i : %s\n", i, cmds->args[i]);
			i++;
		}
		i = 0;
		if (cmds->builtin)
			printf("builtin : %i\n", cmds->builtin);
		if (cmds->path)
			printf("path : %s\n", cmds->path);
		cmds = cmds->next;
	}
	
}

void	print_lexer(t_data *shell)
{
	t_token *token;

	token = shell->token_list;
	while(token)
	{
		printf("Str: %s\n", token->str);
		printf("Pos: %i\n", token->pos);
		printf("Type: %i\n", token->type);
		token = token->next;
	}
}

void	print_env(t_data *shell)
{
	int	i;

	i = 0;
	while (shell->envp[i])
	{
		printf("%s\n", shell->envp[i]);
		i++;
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data shell;

	(void)argc;
	(void)argv;
	ft_memset(&shell, 0, sizeof(t_data));
	create_env(&shell, envp);
	//print_env(&shell);
	//signals();
	while (1)
	{
		input_get(&shell);
		lexer(&shell);
		parser(&shell);
		
		//print_lexer(&shell);
		//print_cmds(&shell);
		executor(&shell);
		free_all(&shell);
	}
}

/*
change SHELL=/bin/zsh???

free/error/exit
rl_clear_history??
exit codes
$?

here doc
signal handler

makefile for linux

// executor
check for read rights in input file
check for write rights in output file
check for execution rights in commands
*/
