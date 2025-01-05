# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbany <mbany@student.42warsaw.pl>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/19 16:44:33 by ltomasze          #+#    #+#              #
#    Updated: 2025/01/05 15:54:12 by mbany            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes -g
SRCS = src/main.c \
src/libft.c \
src/envp.c \
src/signals.c \
src/free.c \
src/check_syntax.c \
src/error.c \
src/utils.c \
src/sanitize.c \
src/commands.c \
src/tokens.c \
src/tokens2.c \
src/clean_toknes.c \
src/dollar.c \
src/token_satinization.c \
src/cmd_redir.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS)  $(OBJS) -o $(NAME) -lreadline

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
