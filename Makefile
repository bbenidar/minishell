# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/30 14:11:37 by bbenidar          #+#    #+#              #
#    Updated: 2023/05/03 14:49:21 by bbenidar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = MINISHELL

CC	= cc
FLAGS = -Wall -Wextra -Werror

SRC =  ./parsing/first_check.c ./parsing/check_utils.c minishell.c \
		./lexical/lexical_func.c ./utils/utils1.c ./utils/utils2.c \
		./parsing/splite_utile.c 

OBG = ${SRC:.c=.o}

minishell : ${OBG}
	cc ${OBG} -o minishell -lreadline

all : minishell

%.o : %.c 
	${CC} ${FLAGS} -c $< -o $@


fclean : clean
	rm -rf minishell
	
clean :
	rm -rf ${OBG}


