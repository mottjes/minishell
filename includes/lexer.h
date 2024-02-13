/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 20:29:53 by mottjes           #+#    #+#             */
/*   Updated: 2024/02/13 14:18:47 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef struct s_data	t_data;

typedef enum s_error	t_error;

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
int		tokens_count(char *input, int *restart);
void	token_list_init(int count, t_token **token_ptr, t_data *shell);
void	tokens_str_cpy(char *input, t_token **token_ptr, t_data *shell);
void	tokens_identify(t_token **token_ptr);

//			lexer_utils.c
int		check_for_quotes(char *input, int *restart, int i);
int		get_str_size(char *input, int i, int size);
void	set_shlvl(t_data *shell);
char	*copy_env_var(char *old_str, int i, char *envp, int len_var);
char	*remove_env_var(char *old_str, int i, int len_var);

#endif
