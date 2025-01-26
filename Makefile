# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbany <mbany@student.42warsaw.pl>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/19 16:44:33 by ltomasze          #+#    #+#              #
#    Updated: 2025/01/26 11:24:52 by mbany            ###   ########.fr        #
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

# Source files
SRCS = src/main.c \
src/libft00.c \
src/libft01.c \
src/libft02.c \
src/libft03.c \
src/envp00.c \
src/envp01.c \
src/signals.c \
src/free.c \
src/check_syntax00.c \
src/check_syntax01.c \
src/error.c \
src/utils.c \
src/sanitize00.c \
src/sanitize01.c \
src/commands00.c \
src/commands01.c \
src/tokens.c \
src/tokens2.c \
src/clean_toknes.c \
src/dollar.c \
src/token_satinization.c \
src/cmd_redir.c \
src/builtin.c \
src/builtin_pwd.c \
src/builtin_export.c \
src/builtin_unset.c \
src/builtin_cd.c\
src/execute00.c \
src/execute01.c \
src/execute02.c \
src/file_descriptor_handlers.c \
src/builtin_echo.c \
src/get_next_line.c

# Object files
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
