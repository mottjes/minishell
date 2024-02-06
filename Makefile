# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/08 14:33:05 by mottjes           #+#    #+#              #
#    Updated: 2024/02/06 14:10:54 by mottjes          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC =	src/main.c					\
		src/signals/signals.c		\
		src/lexer/input.c			\
		src/lexer/lexer.c 			\
		src/lexer/expansion.c		\
		src/lexer/env_var.c			\
		src/lexer/lexer_utils.c		\
		src/parser/parser.c			\
		src/parser/syntax_check.c	\
		src/parser/cmd_table_init.c \
		src/parser/parser_utils.c	\
		src/executor/executor.c		\
		src/executor/builtins.c		\
		src/error/error.c			\
		
CC = gcc

CFLAGS = -Wall -Wextra -Werror

LIBS = libft/libft.a

all:
	@$(MAKE) bonus -C ./libft
	@$(CC) $(CFLAGS) $(SRC) $(LIBS) -o $(NAME) -I${PWD}/readline/include -L${PWD}/readline/lib -lreadline -lhistory -ltermcap
	@echo compiled minishell
	
clean:
	@rm -f $(OBJS)
	@$(MAKE) -C ./libft clean
	@echo cleaned minishell
	
fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C ./libft fclean
	@echo fcleaned minishell
	
re: fclean all

.PHONY: all bonus clean fclean re