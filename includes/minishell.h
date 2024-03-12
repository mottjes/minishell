/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frbeyer <frbeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 14:32:26 by mottjes           #+#    #+#             */
/*   Updated: 2024/03/12 16:25:42 by frbeyer          ###   ########.fr       */
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
typedef struct s_cmd	t_cmd;

//----------------- Main data-structure -----------------//

typedef struct s_data
{
	char		*input;
	char		**envp;
	t_token		*token_list;
	t_cmd		*cmd_list;
	char		*in_file;
	char		*out_file;
	int			fd_built_in;
	int			fd_heredoc;
	int			exit_status;
	int			cmd_count;
	int			count_heredoc;
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
	int				pid;
	struct s_cmd	*next;
}		t_cmd;

//-----------------	 	Functions 		-----------------//

// 			environment.c
void	create_environment(t_data *shell, char **envp);
void	set_shlvl(t_data *shell);

//			input.c
void	input(t_data *shell);

//			signals.c
void	signals(void);
void	signals_child(void);
void	signal_handler(int signal);
void	signal_handler_child(int signal);

//				error.c
void	free_all(t_data *shell);
void	free_environment(t_data *shell);

// 				fail.c
void	malloc_fail(t_data *shell);
void	pipe_fail(t_data *shell);
void	child_fail(t_data *shell);

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
void	exit_status_copy(t_data *shell, int i);
void	expansion_exit_status(t_data *shell);

//			expander_utils2.c
int		skip_single_quotes(t_data *shell, int i);
char	*search_env_var(t_data *shell, int i, int len);
char	*copy_env_var(char *old_str, int i, char *envp, int len_var);
char	*remove_env_var(t_data *shell, int i, int len_var);

//-----------------		 Lexer 			-----------------//

//			lexer.c
void	lexer(t_data *shell);
void	token_list_init(t_data *shell, int count);
void	tokens_str_cpy(t_data *shell);
void	tokens_identify(t_token *token_list);

//			lexer_utils.c
int		tokens_count(char *input, int *restart);
int		check_for_quotes(char *input, int *restart, int i);
int		get_str_size(t_data *shell, int i);

//-----------------	 	 Parser 		-----------------//

//			parser.c
void	builtin_check(t_cmd *cmd_list);
void	search_path(t_data *shell, t_cmd *cmds);
int		path_given(t_data *shell, t_cmd *cmds);
void	cmd_get_path(t_cmd *cmds, t_data *shell);
void	parser(t_data	*shell);

//			cmd_table_init.c
void	cmd_table_init(t_data *shell);
void	cmds_str_copy(t_token *token, t_cmd *cmds, t_data *shell);
void	get_redirections(t_data *shell);
void	cmd_list_init(t_data *shell, int count);

//			syntax.c
void	syntax_pipe(t_token *token, int *restart);
void	check_before(t_token *token_prev_2, t_token *token, int *restart);
void	syntax_redirections(t_token *token, int *restart);
void	syntax_commands(t_token *token, int *restart);
void	syntax_error(int i, int *restart);

//			parser_utilc.c
int		arg_count(t_token *token);
int		cmds_count(t_token *token);

//-----------------	 	 Executor 		-----------------//

//			executor.c
void	executor(t_data *shell);

//			executor_one_cmd.c
void	execute_one_cmd(t_data *shell, t_cmd *cmds);

//			executor_multiple_cmds.c
void	execute_multiple_cmds(t_data *shell, t_cmd *cmds);

// 			executor_utils.c
int		re_output(t_data *shell);
void	exec_built_in(t_data *shell, t_cmd *cmd);
int		count_cmds(t_data *shell);
int		check_rights(t_data *shell);

//			heredoc.c
int		has_heredoc(t_data *shell);
void	capture_heredoc(t_data *shell);

//-----------------	 	 Builtins 		-----------------//

//			export.c
void	export(t_data *shell, t_cmd *cmd);
void	compare_to_env_vars(t_data *shell, t_cmd *cmd, int i);
void	add_env_var(t_data *shell, t_cmd *cmd, int j);
void	print_export(t_data *shell);
int		valid_argument(char *var);

//			export_utils.c
void	sort_envp(t_data *shell, int size);
void	delete_env_var(t_data *shell, int j);
void	create_new_envp(t_data *shell, char ***ptr, int j);

//			echo.c
void	echo(t_data *shell, t_cmd *cmd);

//			cd.c
void	cd(t_data *shell, t_cmd *cmd);

//			env.c
void	env(t_data *shell, t_cmd *cmd);

//			pwd.c
void	pwd(t_data *shell);

//			exit.c
void	ft_exit(t_data *shell, t_cmd *cmd);

//			unset.c
void	unset(t_data *shell, t_cmd *cmd);

#endif
