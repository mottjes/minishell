# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mika <mika@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/08 14:33:05 by mottjes           #+#    #+#              #
#    Updated: 2024/09/26 16:00:46 by mika             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC =	src/main.c									\
		src/builtins/cd.c							\
		src/builtins/echo.c							\
		src/builtins/env.c							\
		src/builtins/exit.c							\
		src/builtins/export_utils.c					\
		src/builtins/export.c						\
		src/builtins/pwd.c							\
		src/builtins/unset.c						\
		src/environment/environment.c				\
		src/error/error.c							\
		src/error/free.c							\
		src/executor/executor_builtins.c			\
		src/executor/executor_multiple_cmds.c		\
		src/executor/executor_one_cmd.c				\
		src/executor/executor_utils.c				\
		src/executor/executor.c						\
		src/expander/expander_env_vars.c			\
		src/expander/expander_redirections.c		\
		src/expander/expander_utils.c				\
		src/expander/expander.c						\
		src/input/input.c							\
		src/lexer/lexer_utils.c						\
		src/lexer/lexer_utils2.c					\
		src/lexer/lexer.c							\
		src/parser/heredoc.c						\
		src/parser/init_cmd_table.c					\
		src/parser/parser_utils.c					\
		src/parser/parser.c							\
		src/parser/redirections.c					\
		src/parser/syntax.c							\
		src/signals/signals.c						\
	
OBJ = $(SRC:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror -no-pie

LIBFT = libft/libft.a

GREEN = "\033[1;32m"

YELLOW = "\033[1;33m"

RED = "\033[1;31m"

NONE = "\033[0m"

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBFT) -lreadline -lhistory
	@echo $(GREEN)$(NAME) compiled $(NONE)
	
%.o: %.c
	@$(CC) $(CFLAGS) -I./readline -I./libft -c -o $@ $<

$(LIBFT):
	@$(MAKE) bonus -C ./libft
	@echo $(YELLOW)libft compiled$(NONE)

clean:
	@rm -f $(OBJ)
	@$(MAKE) -C ./libft clean
	@echo $(RED)cleaned $(NAME)$(NONE)
	
fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C ./libft fclean
	@echo $(RED)fcleaned $(NAME)$(NONE)
	
re: fclean all

.PHONY: all bonus clean fclean re $(LIBFT)