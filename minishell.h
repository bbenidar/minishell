/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:34:27 by bbenidar          #+#    #+#             */
/*   Updated: 2023/05/07 15:26:00 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>

enum t_type{
	COMMAND = 1,	
	OPTION,	
	SPACES,	
	RED_APP,	
	RED_OUT,	
	RED_IN,	
	RED_HER,
	FILE_IN,
	FILE_OUT,
	FILE_APP,
	PIPE,
};

typedef struct b_var
{
    char **str;
} t_var;

typedef struct b_stack
{
	char				*word;
	int			key;
	struct b_stack	*next;

}					t_stack;
// ---------------------------------UTILS FUNCT-------------------------------//
//util/utils1.c
int	ft_strlen(const char *str);
char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, int start,
		int len);
//util/utils2.c
char	*ft_strdup(const char *s1);
int	ft_isalpha(int c);



// ---------------------------------PRINC FUNCT-------------------------------//
//parsing/first_check.c
int ft_first_check(char *str);
int check_space(char *str);
//parsing/check_utils.c
int check_character(char c, char *check);
//lexical/lexical_func
void lexical_function(char *line);
char	**ft_split_opera(char const *s);
int	ft_strncmp(const char *s1, const char *s2, size_t n);

#endif