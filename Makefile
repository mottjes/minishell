# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mottjes <mottjes@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/08 14:33:05 by mottjes           #+#    #+#              #
#    Updated: 2024/01/08 17:22:29 by mottjes          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = src/main.c	\

CC = gcc

CFLAGS = -Wall -Wextra -Werror 

all:
	$(CC) $(SRC) -o $(NAME) -I${PWD}/readline/include -L${PWD}/readline/lib -lreadline -lhistory -ltermcap
