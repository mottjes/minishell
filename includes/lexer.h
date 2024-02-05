/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 20:29:53 by mottjes           #+#    #+#             */
/*   Updated: 2024/02/05 17:24:40 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef struct s_data t_data;

typedef enum s_error t_error;

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
void	lexer(t_data *shell);
int		tokens_count(char *input, t_error *error);
void 	token_list_init(int count, t_token **token_ptr, t_error *error);
void	tokens_str_cpy(char *input, t_token **token_ptr, t_error *error);
void	tokens_identify(t_token **token_ptr);

//			lexer_utils.c
int		check_for_quotes(char *input, t_error *error, int i);
int		get_str_size(char *input, int i, int size);

//			expansion.c
void	input_expansion(char **input_ptr, t_error *error);
int		check_after_operator(char **input_ptr, int i, t_error *error);
int		check_before_operator(char **input_ptr, int i, t_error *error);
void	add_space(char **input_ptr, int i, t_error *error);

//			env_var.c
void	get_env_vars(t_data *shell);
char	*copy_env_var_in_str(char *old_str, int pos_in_str, char *envp, int len_var);

#endif
