/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:50:56 by mottjes           #+#    #+#             */
/*   Updated: 2024/03/19 15:48:11 by mottjes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <errno.h>
# include "../libft/libft.h"
# define READLINE_LIBRARY
# include "../readline/include/history.h"
# include "../readline/include/readline.h"

typedef struct s_token	t_token;
typedef struct s_cmd	t_cmd;

//----------------- Main Data Structure -----------------//

typedef struct s_data
{
	char	**envp;
	char	*input;
	t_token	*token_lst;
	t_cmd	*cmd_lst;
	bool	restart;
	int		cmd_count;
	int		exit_status;
}			t_data;

//---------------- Token Data Structure -----------------//

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
	int				pos;
	t_token_type	type;
	struct s_token	*next;
}			t_token;

//--------------- Command Data Structure ----------------//

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	bool			builtin;
	char			*path;
	char			*in_file;
	char			*out_file;
	int				fd_in;
	int				fd_out;
	bool			out_app;
	int				pid;
	struct s_cmd	*next;
}			t_cmd;

//-------------------- Environment ----------------------//

// 			environment.c
void	init_environment(t_data *shell, char **envp);

//---------------------- Signals ------------------------//

// 			signals.c
void	signals_child(void);
void	signals(void);

//----------------------- Input -------------------------//

// 			input.c
void	input(t_data *shell);

//---------------------- Expander ------------------------//

//			expander_env_vars.c
int		skip_single_quotes(t_data *shell, int i);
char	*remove_env_var(t_data *shell, int i, int len_var);
char	*add_env_var(t_data *shell, int j, int i, int len_var);
char	*search_env_var(t_data *shell, int i, int len_var);
void	expansion_env_var(t_data *shell, int i);

// 			expander_redirections.c
void	expansion_after_redirections(t_data *shell);
void	expansion_before_redirections(t_data *shell);

// 			expander_utils.c
int		skip_quotes(char *str, int i);
void	add_space(t_data *shell, int i);
void	add_exit_status(t_data *shell, int i);
int		check_after_operator(t_data *shell, int i);
int		check_before_operator(t_data *shell, int i);

// 			expander
void	expander(t_data *shell);

//----------------------- Lexer -------------------------//

// 			lexer.c
void	lexer(t_data *shell);
void	token_lst_init(t_data *shell, int count);
void	tokens_identify(t_data *shell);
void	tokens_str_copy(t_data *shell);
int		token_add_str(t_data *shell, t_token *token, int i);

// 			lexer_utils.c
int		tokens_count(char *input, bool *restart, int count, int i);
void	set_token_type(t_data *shell, t_token *token, int i);
int		get_str_size(t_data *shell, int i);

//----------------------- Parser ------------------------//

// 			heredoc.c
void	capture_heredoc(t_data *shell, t_token *token, t_cmd *cmd);
void	unset_heredoc(t_token *token, t_cmd *cmd);

// 			init_cmd_table.c
void	cmds_str_copy(t_data *shell, t_token *token, t_cmd *cmd);
void	cmd_list_init(t_data *shell, int count);
void	init_cmd_table(t_data *shell);

// 			parser_utils.c
void	search_path(t_data *shell, t_cmd *cmds);
bool	check_path_given(t_data *shell, t_cmd *cmd);
int		cmds_count(t_token *token);
int		arg_count(t_token *token);

// 			parser.c
void	parser(t_data *shell);

// 			redirections.c
void	get_redirections(t_data *shell, t_token *token);

// 			syntax.c
void	syntax_error(int i, bool *restart);
void	syntax_commands(t_token *token, bool *restart);
void	syntax_redirections(t_token *token, bool *restart);

//--------------------- Executor ------------------------//

// 			executor_builtins.c
void	exec_built_in(t_data *shell, t_cmd *cmd);

// 			executor_multiple_cmds.c
void	execute_multiple_cmds(t_data *shell, t_cmd *cmds);

// 			executor_one_cmd.c
void	execute_one_cmd(t_data *shell, t_cmd *cmds);

// 			executor_utils.c
int		re_output(t_data *shell, t_cmd *cmds);
int		count_cmds(t_data *shell);

// 			executor.c
void	executor(t_data *shell);

//--------------------- Builtins  -----------------------//

// 			cd.c
void	cd(t_data *shell, t_cmd *cmd);

// 			echo.c
void	echo(t_data *shell, t_cmd *cmd);

// 			env.c
void	env(t_data *shell, t_cmd *cmd);

// 			exit.c
void	ft_exit(t_data *shell, t_cmd *cmd);

// 			export_utils.c
void	create_new_envp(t_data *shell, char ***ptr, int j);
void	delete_env_var(t_data *shell, int j);
void	sort_envp(t_data *shell, int size);

// 			export.c
void	export(t_data *shell, t_cmd *cmd);

// 			pwd.c
void	pwd(t_data *shell, t_cmd *cmd);

// 			unset.c
void	unset(t_data *shell, t_cmd *cmd);

//--------------------- Error  -----------------------//

// 			error.c
void	pipe_fail(t_data *shell);
void	child_fail(t_data *shell);
void	malloc_fail(t_data *shell);
void	*safe_malloc(size_t bytes, t_data *shell);

// 			free.c
void	free_cmd(t_cmd *cmd);
void	free_cmd_list(t_data *shell);
void	free_environment(t_data *shell);
void	free_all(t_data *shell);

#endif
