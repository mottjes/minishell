/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:56:04 by mottjes           #+#    #+#             */
/*   Updated: 2024/02/12 18:23:19 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_data	t_data;

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	char			*path;
	int				builtin;
	struct s_cmd	*next;
}		t_cmd;

//			parser.c
void	builtin_check(t_cmd *cmd_list);
void	cmd_get_path(t_cmd *cmds, t_data *shell);
void	parser(t_data	*shell);

//			cmd_table_init.c
void	cmd_table_init(t_data *shell);
void	cmds_str_copy(t_token *token, t_cmd *cmds, t_data *shell);
void	get_redirections(t_data *shell);
void	cmd_list_init(t_data *shell, int count);

//			syntax_check.c
void	syntax_pipe(t_token *token, int *restart);
void	syntax_redirections(t_token *token, int *restart);
void	syntax_commands(t_token *token, int *restart);

//			parser_utilc.c
int		arg_count(t_token *token);
int		cmds_count(t_token *token);

#endif
