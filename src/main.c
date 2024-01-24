/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 14:33:44 by mottjes           #+#    #+#             */
/*   Updated: 2024/01/24 17:55:49 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void print_lexer(t_token *token)
// {
// 	while(token)
// 	{
// 		printf("pos: %d\n", token->pos);
// 		printf("str: %s\n", token->str);
// 		printf("type: %d\n", token->type);
// 		token = token->next;
// 	}
// }

// void	tokens_free(t_token **token_ptr)
// {
// 	t_token *next;
// 	t_token	*current;

// 	current = *token_ptr;
// 	while (current)
// 	{
// 		next = current->next;
// 		free(current->str);
// 		free (current);
// 		current = next;
// 	}
// 	*token_ptr = NULL;
// }

// void	print_cmds(t_minishell *shell)
// {
// 	t_cmd *cmd;
// 	int i;

// 	i = 0;
// 	cmd = shell->cmd_list;
// 	printf("infile :%s\n", shell->in_file);
// 	printf("outfile :%s\n", shell->out_file);
	
// 	printf("cmd : %s\n", cmd->cmd);
// 	printf("builtin : %i\n", cmd->builtin);
// 	// while (cmd->args[i])
// 	// {
// 	// 	printf("arg %i: %s\n", i, cmd->args[i]);
// 	// 	i++;
// 	// }
// 	// i = 0;
// 	cmd = cmd->next;
// 	printf("cmd : %s\n", cmd->cmd);
// 	printf("builtin : %i\n", cmd->builtin);
// 	// while (cmd->args[i])
// 	// {
// 	// 	printf("arg %i: %s\n", i, cmd->args[i]);
// 	// 	i++;
// 	// }
// 	// i = 0;
// }

int	main(int argc, char *argv[], char *envp[])
{
	t_minishell shell;

	while (1)
	{
		//signals();
		get_promt(&shell.input);
		lexer(&shell);
		parser(&shell);

	
		//print_lexer(shell.token_list);
		//print_cmds(&shell);
	}
}
