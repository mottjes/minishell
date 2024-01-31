/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 14:32:26 by mottjes           #+#    #+#             */
/*   Updated: 2024/01/31 15:10:43 by mottjes          ###   ########.fr       */
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

//				promt.c
void	get_promt(t_data *shell);

//				signals.c
void	signals(void);
void	signal_handler(int signal);

//				builtins.c
void	env(char *envp[]);
void	pwd(void);
void	cd(char *path);

#endif