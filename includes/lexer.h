/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 20:29:53 by mottjes           #+#    #+#             */
/*   Updated: 2024/01/15 19:00:43 by mottjes          ###   ########.fr       */
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

void	lexer(char **input,t_token **token);


#endif
