# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/08 14:33:05 by mottjes           #+#    #+#              #
#    Updated: 2024/01/18 14:38:56 by mottjes          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC =	src/main.c				\
		src/promt.c				\
		src/lexer/lexer.c 		\
		src/lexer/input_split.c	\
		src/signals.c			\
		
CC = gcc

CFLAGS = -Wall -Wextra -Werror -fsanitize=address

LIBS = libft/libft.a

all:
	@$(MAKE) -C ./libft
	@$(CC) $(SRC) $(LIBS) -o $(NAME) -I${PWD}/readline/include -L${PWD}/readline/lib -lreadline -lhistory -ltermcap
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