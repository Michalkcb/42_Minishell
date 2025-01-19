# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbany <mbany@student.42warsaw.pl>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/19 16:44:33 by ltomasze          #+#    #+#              #
#    Updated: 2025/01/19 12:23:09 by mbany            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# NAME = minishell
# CC = cc
# CFLAGS = -Wall -Wextra -Werror -Iincludes -g
# SRCS = src/main.c \
# src/libft.c \
# src/envp.c \
# src/signals.c \
# src/free.c \
# src/check_syntax.c \
# src/error.c \
# src/utils.c \
# src/sanitize.c \
# src/commands.c \
# src/tokens.c \
# src/tokens2.c \
# src/clean_toknes.c \
# src/dollar.c \
# src/token_satinization.c \
# src/cmd_redir.c \
# src/buildin.c \
# src/builtin_export.c \
# src/builtin_unset.c \
# src/builtin_cd.c

# OBJS = $(SRCS:.c=.o)

# all: $(NAME)

# $(NAME): $(OBJS)
# 	$(CC) $(CFLAGS)  $(OBJS) -o $(NAME) -lreadline

# clean:
# 	rm -f $(OBJS)

# fclean: clean
# 	rm -f $(NAME)

# re: fclean all


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
src/cmd_redir.c \
src/buildin.c \
src/builtin_export.c \
src/builtin_unset.c \
src/builtin_cd.c\
src/execute.c \
src/file_descriptor_handlers

OBJ_DIR = obj
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline

$(OBJ_DIR)/%.o: %.c | prepare_dirs
	$(CC) $(CFLAGS) -c $< -o $@

prepare_dirs:
	mkdir -p $(OBJ_DIR)/src

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
