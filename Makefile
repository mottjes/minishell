# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frbeyer <frbeyer@student.42wolfsburg.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/08 14:33:05 by mottjes           #+#    #+#              #
#    Updated: 2024/02/21 17:03:16 by frbeyer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC =	src/main.c						\
		src/environment/environment.c	\
		src/signals/signals.c			\
		src/input/input.c				\
		src/expander/expander.c			\
		src/lexer/lexer.c 				\
		src/lexer/lexer_utils.c			\
		src/parser/parser.c				\
		src/parser/syntax.c				\
		src/parser/cmd_table_init.c 	\
		src/parser/parser_utils.c		\
		src/executor/executor.c			\
		src/executor/builtins.c			\
		src/executor/cd.c				\
		src/error/error.c				\
		
CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

OBJ = $(SRC:.c=.o)

LIBFT = libft/libft.a

READLINE_PATH = $(PWD)/readline

GREEN = "\033[1;32m"

YELLOW = "\033[1;33m"

RED = "\033[1;31m"

NONE = "\033[0m"

UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
	LIBREADLINE_FLAGS = -lreadline -lhistory
else ifeq ($(UNAME), Darwin)
	LIBREADLINE_FLAGS = -I$(READLINE_PATH)/include -L$(READLINE_PATH)/lib -lreadline -lhistory -ltermcap
endif

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBFT) $(LIBREADLINE_FLAGS)
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