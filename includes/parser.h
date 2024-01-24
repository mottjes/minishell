/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:56:04 by mottjes           #+#    #+#             */
/*   Updated: 2024/01/24 17:53:51 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_minishell t_minishell;

typedef	struct s_cmd
{
	char			*cmd;
	char			**args;
	char			*path;
	int				builtin;
	struct s_cmd	*next;

}		t_cmd;

//				parser.c
void	parser(t_minishell	*shell);

//				cmd_table_init.c
void	cmd_table_init(t_minishell *shell);
void	cmds_str_copy(t_minishell *shell);
void	get_redirections(t_minishell *shell);
void	cmd_list_init(t_minishell *shell, int count);
int		arg_count(t_token *token);
int		cmds_count(t_token *token);

//				syntax_check.c
void	syntax_check(t_token *token);

#endif
