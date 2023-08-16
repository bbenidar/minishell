# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/30 14:11:37 by bbenidar          #+#    #+#              #
#    Updated: 2023/08/16 16:02:27 by bbenidar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC	= cc
FLAGS = -Wall -Wextra -Werror

SRC =  	./parsing/first_check.c ./parsing/first_check_2.c ./parsing/check_utils.c minishell.c ./utils/utils3.c ./lexical/ft_dell_space.c \
		./lexical/lexical_func.c  ./lexical/checking_.c  ./lexical/ft_herdoc.c  ./lexical/ft_herdoc_utils.c ./lexical/ft_split_in_list.c \
		./lexical/ft_option.c ./lexical/add_variabl.c ./lexical/add_variabl_utils.c  ./lexical/lexical_utils.c ./lexical/linked_list_creation.c ./utils/utils1.c ./utils/utils5.c ./utils/utils2.c  \
		./parsing/splite_utile.c  ./utils/utils4.c ./utils/itoa.c ./execution/execut.c ./execution/execut_help.c  ./lexical/ft_last_list.c ./lexical/ft_last_list_utils.c ./execution/builting/echo.c\
		./execution/builting/cd.c ./execution/builting/env.c execution/builting/export.c execution/builting/pwd.c  execution/check_for_b.c execution/execut_utils.c \
		execution/builting/unset.c  execution/builting/export_utils.c execution/builting/export_utils_2.c 	utils/atoll.c execution/builting/exit.c envir/no_env_entr.c envir/envir_rep.c 
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

minishell : ${OBG} minishell.h
	cc $(FLAGS) ${OBG} -L $(shell brew --prefix readline)/lib -lreadline -o minishell
	@echo $(HEAD)

%.o : %.c minishell.h
	${CC} ${FLAGS} -I $(shell brew --prefix readline)/include -c $< -o $@

fclean : clean
	rm -rf minishell
	
clean :
	rm -rf ${OBG}

re : fclean all
