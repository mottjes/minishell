/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 20:29:53 by mottjes           #+#    #+#             */
/*   Updated: 2024/01/16 15:01:40 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef enum s_token_type
{
	WORD,					// string
	PIPE,					// pipe 
	RE_IN,					// redirects input
	RE_OUT,					// redirects output
	RE_APP,					// redirects output in append mode
	HERE_DOC,				// delimiter
}			t_token_type;

typedef struct s_token
{
	char			*str;
	t_token_type	type;
	int				pos;
	struct s_token	*next;
}		t_token;

//			promt.c
void	lexer(char **input,t_token **token);

//			lexer.c
void	lexer(char **input, t_token **token_ptr);
void	tokens_identify(t_token **token_ptr);
void 	tokens_str_cpy(char *input, t_token **token_ptr);
void 	tokens_init(char *input, int count, t_token **token_ptr);
int		tokens_count(char *input);


#endif
