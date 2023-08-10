# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sakarkal <sakarkal@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/30 14:11:37 by bbenidar          #+#    #+#              #
#    Updated: 2023/08/10 10:40:38 by sakarkal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = MINISHELL

CC	= cc
FLAGS = -Wall -Wextra -g #-Werror

SRC =  	./parsing/first_check.c ./parsing/check_utils.c minishell.c ./utils/utils3.c\
		./lexical/lexical_func.c  ./lexical/checking_.c  ./lexical/ft_herdoc.c  ./lexical/ft_herdoc_utils.c \
		./lexical/ft_option.c ./lexical/add_variabl.c ./lexical/add_variabl_utils.c  ./lexical/linked_list_creation.c ./utils/utils1.c ./utils/utils5.c ./utils/utils2.c  \
		./parsing/splite_utile.c  ./utils/utils4.c ./utils/itoa.c ./execution/executt.c  ./execution/builting/echo.c\
		./execution/builting/cd.c ./execution/builting/env.c execution/builting/export.c execution/builting/pwd.c\
		execution/builting/unset.c	utils/atoll.c execution/builting/exit.c envir/no_env_entr.c envir/envir_rep.c \
		garbage_lst.c execution/builting/export_utils.c parsing/checking_utl.c\
		execution/check_built.c execution/check_exec.c execution/close_pipe.c execution/execut_utils.c execution/lst_last_size.c
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
