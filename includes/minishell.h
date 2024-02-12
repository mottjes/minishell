/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 14:32:26 by mottjes           #+#    #+#             */
/*   Updated: 2024/02/12 18:23:25 by mottjes          ###   ########.fr       */
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

# define CYAN	"\x1b[36m"
# define RESET	"\x1b[0m"
# define BOLD	"\033[1m"

typedef struct s_data
{
	char		*input;
	t_token		*token_list;
	t_cmd		*cmd_list;
	t_exec		*exec_list;
	char		*in_file;
	char		*out_file;
	char		**envp;
	int			restart;
}		t_data;

//				signals.c
void	signals(void);
void	signal_handler(int signal);

//				error.c
void	free_all(t_data *shell);
void	malloc_fail(t_data *shell);

#endif