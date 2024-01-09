/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 20:29:53 by mottjes           #+#    #+#             */
/*   Updated: 2024/01/09 18:35:19 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
/*

lexer:
lexical analysis where the input is read char by char to form tokens

1.	word 
2.	'-'
'|'	
'<'
'>'
'>>'
'<<'
*/

typedef struct s_lexer
{
	char	*value;
	
	int		pos;
	s_lexer	*next;
}		t_lexer;



#endif
