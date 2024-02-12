/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 20:29:53 by mottjes           #+#    #+#             */
/*   Updated: 2024/02/12 18:23:41 by mottjes          ###   ########.fr       */
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

//				input.c
void	input_get(t_data *shell);
char	*build_promt(t_data *shell, char *cwd);

//			lexer.c
void	lexer(t_data *shell);
int		tokens_count(char *input, int *restart);
void	token_list_init(int count, t_token **token_ptr, t_data *shell);
void	tokens_str_cpy(char *input, t_token **token_ptr, t_data *shell);
void	tokens_identify(t_token **token_ptr);

//			lexer_utils.c
int		check_for_quotes(char *input, int *restart, int i);
int		get_str_size(char *input, int i, int size);

//			expansion.c
void	input_expansion(char **input_ptr, t_data *shell);
int		check_after_operator(char **input_ptr, int i, t_data *shell);
int		check_before_operator(char **input_ptr, int i, t_data *shell);
void	add_space(char **input_ptr, int i, t_data *shell);

//			env_var.c
void	create_env(t_data *shell, char **envp);
void	get_env_vars(t_data *shell);
void	set_shlvl(t_data *shell);
char	*copy_env_var(char *old_str, int i, char *envp, int len_var);
char	*remove_env_var(char *old_str, int i, int len_var);

#endif
