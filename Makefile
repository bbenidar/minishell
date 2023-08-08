# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/30 14:11:37 by bbenidar          #+#    #+#              #
#    Updated: 2023/08/08 18:16:53 by bbenidar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = MINISHELL

CC	= cc
FLAGS = -Wall -Wextra -g #-Werror

SRC =  	./parsing/first_check.c ./parsing/check_utils.c minishell.c ./utils/utils3.c\
		./lexical/lexical_func.c  ./lexical/checking_.c  ./lexical/ft_herdoc.c  ./lexical/ft_herdoc_utils.c \
		./lexical/ft_option.c ./lexical/linked_list_creation.c ./utils/utils1.c ./utils/utils5.c ./utils/utils2.c  \
		./parsing/splite_utile.c  ./utils/utils4.c ./utils/itoa.c ./execution/execut.c  ./execution/builting/echo.c\
		./execution/builting/cd.c ./execution/builting/env.c execution/builting/export.c execution/builting/pwd.c\
		execution/builting/unset.c	utils/atoll.c execution/builting/exit.c envir/no_env_entr.c envir/envir_rep.c \
		garbage_lst.c
OBG = ${SRC:.c=.o}

HEAD="\n"\
	"███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     \n"\
	"████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     \n"\
	"██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     \n"\
	"██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     \n"\
	"██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗\n"\
	"╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n"\
	"      Made by : \033[1;91msakarkal\033[m and \033[1;91mbbenidar\033[m\n"


all : minishell

minishell : ${OBG}
	cc $(FLAGS) ${OBG} -L $(shell brew --prefix readline)/lib -lreadline -o minishell
	@echo $(HEAD)

%.o : %.c 
	${CC} ${FLAGS} -I $(shell brew --prefix readline)/include -c $< -o $@

fclean : clean
	rm -rf minishell
	
clean :
	rm -rf ${OBG}

re : fclean all
