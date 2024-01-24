/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 14:32:26 by mottjes           #+#    #+#             */
/*   Updated: 2024/01/24 14:17:00 by mottjes          ###   ########.fr       */
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

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"
#define BOLD	"\033[1m"

typedef	struct s_minishell
{
	char		*input;
	t_token		*token_list;
	t_cmd		*cmd_list;
	char		*in_file;
	char		*out_file;
	char		**envp;
	int			error;
}		t_minishell;

//				promt.c
void	get_promt(char **input);

//				signals.c
void	signals(void);
void	signal_handler(int signal);

//				builtins.c
void	env(char *envp[]);
void	pwd(void);
void	cd(char *path);

#endif