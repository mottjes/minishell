/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 14:33:44 by mottjes           #+#    #+#             */
/*   Updated: 2024/03/04 14:24:54 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int g_status;

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

int	main(int argc, char *argv[], char *envp[])
{
	t_data shell;

	(void)argc;
	(void)argv;
	ft_memset(&shell, 0, sizeof(t_data));
	create_environment(&shell, envp);
	signals();
	while (1)
	{
		input(&shell);
		expander(&shell);
		lexer(&shell);
		parser(&shell);
		
		// print_lexer(&shell);
		// print_cmds(&shell);
		executor(&shell);
		free_all(&shell);
	}
}

/*
here doc

// executor
check for read rights in input file
check for write rights in output file
check for execution rights in commands

signals:
use signal() not sigaction

builtins:
check for right arg count
export:	put multiple vars in env and check if there are there -> update 
same for unset
put cmd instead of var in the functions
check for args pwd -> error

exit:
rl_clear_history??
exit status


promt
*/
