# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/12 15:20:15 by mphobos           #+#    #+#              #
#    Updated: 2019/12/29 14:37:33 by mphobos          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRC = main.c execute_cd.c environ.c execute_echo.c execute_setenv.c \
	execute_unsetenv.c execute_bin.c execute_env.c execute_env_sup.c \
	init_call.c execute_sysbin.c
CC = gcc
INCLUDE = includes
CFLAGS = -Wall -Wextra -Werror -L libft -lft -I $(INCLUDE) -o $(NAME)
DFLAGS = $(CFLAGS) -g

%.c:
	$(CC) $(DFLAGS) $(SRC) -c $<

$(NAME): $(SRC)
	make -C libft
	$(CC) $(DFLAGS) $(SRC)

all: $(NAME)

clean:
	make -C libft clean

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
