/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:34:27 by bbenidar          #+#    #+#             */
/*   Updated: 2023/04/30 18:41:17 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

typedef struct b_var
{
    char **str;
} t_var;
// ---------------------------------UTILS FUNCT-------------------------------//
//util/utils1.c
int	ft_strlen(const char *str);
char	**ft_split(char const *s, char c);
//util/utils2.c
char	*ft_strdup(const char *s1);



// ---------------------------------PRINC FUNCT-------------------------------//
//parsing/first_check.c
void ft_first_check(char *str);
int check_space(char *str);

#endif