/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:56:04 by mottjes           #+#    #+#             */
/*   Updated: 2024/01/30 12:01:29 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_data t_data;

typedef	struct s_cmd
{
	char			*cmd;
	char			**args;
	char			*path;
	int				builtin;
	struct s_cmd	*next;
}		t_cmd;

//				parser.c
void	builtin_check(t_cmd *cmd_list);
void	cmd_get_path(t_cmd *cmds, char **envp, t_error *error);
void	parser(t_data	*shell);

//				cmd_table_init.c
void	cmd_table_init(t_data *shell);
void	cmds_str_copy(t_token *token, t_cmd *cmds, t_error *error);
void	get_redirections(t_data *shell);
void	cmd_list_init(t_data *shell, int count, t_error *error);
int		arg_count(t_token *token);
int		cmds_count(t_token *token);

//				syntax_check.c
void	syntax_check(t_token *token);

#endif
