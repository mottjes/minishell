/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 14:32:26 by mottjes           #+#    #+#             */
/*   Updated: 2024/02/05 14:09:33 by mottjes          ###   ########.fr       */
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
# include "lexer.h"
# include "parser.h"
# include "executor.h"
# include "builtins.h"

#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"
#define BOLD	"\033[1m"

typedef enum s_error
{
	malloc_failed = 1,
	quotes_not_closed = 2,
	command_not_found = 3,
	env_var_not_found = 4,
	syntax_error = 5,
}			t_error;

typedef	struct s_data
{
	char		*input;
	t_token		*token_list;
	t_cmd		*cmd_list;
	t_exec		*exec_list;
	char		*in_file;
	char		*out_file;
	char		**envp;
	int			restart;
	t_error		error;
}		t_data;

//				input.c
void	input_get(t_data *shell);
char	*promt_get(t_data *shell, char *cwd);

//				signals.c
void	signals(void);
void	signal_handler(int signal);


void	error_check(t_data *shell);

#endif