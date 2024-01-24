/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:56:04 by mottjes           #+#    #+#             */
/*   Updated: 2024/01/24 13:49:05 by mottjes          ###   ########.fr       */
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


//				syntax_check.c
void	syntax_check(t_token *token);

#endif
