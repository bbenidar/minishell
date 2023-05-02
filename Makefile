# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/30 14:11:37 by bbenidar          #+#    #+#              #
#    Updated: 2023/05/02 10:43:42 by bbenidar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = MINISHELL

CC	= cc
FLAGS = -Wall -Wextra -Werror

SRC =  ./parsing/first_check.c ./parsing/check_utils.c minishell.c 

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


