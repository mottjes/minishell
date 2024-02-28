/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 14:32:26 by mottjes           #+#    #+#             */
/*   Updated: 2024/02/28 13:50:22 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include <signal.h>
# include <errno.h>
# include "../libft/libft.h"
# define READLINE_LIBRARY
# include "../readline/include/history.h"
# include "../readline/include/readline.h"

# define CYAN	"\x1b[36m"
# define RESET	"\x1b[0m"
# define BOLD	"\033[1m"

typedef struct s_token	t_token;
typedef struct s_cmd 	t_cmd;

//----------------- Main data-structure -----------------//

typedef struct s_data
{
	char		*input;
	char		**envp;
	t_token		*token_list;
	t_cmd		*cmd_list;
	char		*in_file;
	char		*out_file;
	int			restart;
}		t_data;

//-----------------	 Token structure	-----------------//

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

//-----------------	 Command structure	-----------------//

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	char			*path;
	int				builtin;
	struct s_cmd	*next;
}		t_cmd;

//-----------------	 	Functions 		-----------------//

// 			environment.c
void	create_environment(t_data *shell, char **envp);
void	set_shlvl(t_data *shell);

//			input.c
void	input(t_data *shell);
char	*build_promt(t_data *shell, char *cwd);

//			signals.c
void	signals(void);
void	signals_child(void);
void	signal_handler(int signal);
void	signal_handler_child(int signal);

//				error
void	free_all(t_data *shell);
void	malloc_fail(t_data *shell);

//-----------------	 	Expander 		-----------------//

//			expander.c
void	expander(t_data *shell);
void	expansion_pipes(t_data *shell);
void	expansion_before_redirections(t_data *shell);
void	expansion_after_redirections(t_data *shell);
void	expansion_env_vars(t_data *shell);

//			expander_utils.c
void	add_space(t_data *shell, int i);
int		check_before_operator(t_data *shell, int i);
int		check_after_operator(t_data *shell, int i);

//			expander_utils2.c
int		skip_single_quotes(t_data *shell, int i);
char	*search_env_var(t_data *shell, int i, int len);
char	*copy_env_var(char *old_str, int i, char *envp, int len_var);
char	*remove_env_var(t_data *shell, int i, int len_var);



//-----------------	 		Lexer 		-----------------//

//			lexer.c
void	lexer(t_data *shell);
int		tokens_count(char *input, int *restart);
void	token_list_init(int count, t_token **token_ptr, t_data *shell);
void	tokens_str_cpy(char *input, t_token **token_ptr, t_data *shell);
void	tokens_identify(t_token **token_ptr);

//			lexer_utils.c
int		check_for_quotes(char *input, int *restart, int i);
int		get_str_size(char *input, int i, int size);

//-----------------	 		Parser 		-----------------//

//			parser.c
void	builtin_check(t_cmd *cmd_list);
void	cmd_get_path(t_cmd *cmds, t_data *shell);
void	parser(t_data	*shell);

//			cmd_table_init.c
void	cmd_table_init(t_data *shell);
void	cmds_str_copy(t_token *token, t_cmd *cmds, t_data *shell);
void	get_redirections(t_data *shell);
void	cmd_list_init(t_data *shell, int count);

//			syntax.c
void	syntax_pipe(t_token *token, int *restart);
void	syntax_redirections(t_token *token, int *restart);
void	syntax_commands(t_token *token, int *restart);

//			parser_utilc.c
int		arg_count(t_token *token);
int		cmds_count(t_token *token);

//-----------------	 		Executor 		-----------------//

//			executor.c
void	executor(t_data *shell);

//          builtins
void	echo(t_data *shell, int i);
void	cd(t_data *shell, t_cmd *cmd);
void	env(t_data *shell);
void	pwd(t_data *shell);
void	ft_exit(t_data *shell);
void	unset(t_data *shell, char *var);
void	export(t_data *shell, char *var);

#endif