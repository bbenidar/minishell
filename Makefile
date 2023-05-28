# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: messoufi <messoufi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/30 14:11:37 by bbenidar          #+#    #+#              #
#    Updated: 2023/05/27 14:32:09 by messoufi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = MINISHELL

CC	= cc
FLAGS = -Wall -Wextra -Werror

SRC =  ./parsing/first_check.c ./parsing/check_utils.c minishell.c \
		./lexical/lexical_func.c ./utils/utils1.c ./utils/utils2.c ./utils/utils3.c \
		./parsing/splite_utile.c 

OBG = ${SRC:.c=.o}

HEAD="\n"\
	"███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     \n"\
	"████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     \n"\
	"██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     \n"\
	"██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     \n"\
	"██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗\n"\
	"╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n"\
	"      Made by : \033[1;91mmessoufi\033[m and \033[1;91mbbenidar\033[m\n"


all : minishell

minishell : ${OBG}
	cc ${OBG} -o minishell -lreadline
	@echo $(HEAD)

%.o : %.c 
	${CC} ${FLAGS} -c $< -o $@

fclean : clean
	rm -rf minishell
	
clean :
	rm -rf ${OBG}

re : fclean all
