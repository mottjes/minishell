/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 20:29:53 by mottjes           #+#    #+#             */
/*   Updated: 2024/01/17 17:18:17 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef enum s_token_type
{
	WORD,
	PIPE,
	RE_IN,
	RE_OUT,
	RE_APP,
	HERE_DOC,
}			t_token_type;

typedef struct s_token
{
	char			*str;
	t_token_type	type;
	int				pos;
	struct s_token	*next;
}		t_token;

//			lexer.c
void	lexer(char **input, t_token **token_ptr);
int		tokens_count(char *input);
void 	tokens_init(char *input, int count, t_token **token_ptr);
void 	tokens_str_cpy(char *input, t_token **token_ptr);
void	tokens_identify(t_token **token_ptr);

//			input_split.c
void	input_split(char **input_ptr);
void	add_space(char **input_ptr, int i);

#endif
