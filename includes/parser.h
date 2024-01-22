/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:56:04 by mottjes           #+#    #+#             */
/*   Updated: 2024/01/22 14:35:55 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PARSER_H
# define PARSER_H

typedef	struct s_cmd
{
	char			*cmd;
	char			**args;
	struct s_cmd	*next;
}		t_cmd;

typedef struct s_cmd_table
{
	t_cmd	*cmds;
	char	*in_file;
	char	*out_file;
}		t_cmd_table;

//				parser.c
void	parser(t_token *token, t_cmd_table *cmd_table);


#endif