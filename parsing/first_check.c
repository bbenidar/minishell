/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 13:26:45 by bbenidar          #+#    #+#             */
/*   Updated: 2023/04/30 18:54:19 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

static int  ft_check_quotes(char *str)
{
   int a;
   int b;
   int i;
   
   a = -1;
   i = 0; 
   b = -1;
   while(str[i])
   {
        if (str[i] == 34 && b == -1)
            a *= -1;
        if (str[i] == 39 && a == -1)
            b *= -1;
        i++;
   }
    if (a == 1 || b == 1)
        return (1);
    return (0);

}

int check_space(char *str)
{
    while(*str == ' ')
        str++;
    if(!*str)
        return (1);
    return (0);
}

void ft_first_check(char *str)
{
    while(*str == ' ')
        str++;
    if(check_space(str))
         return ;  
    if (ft_check_quotes(str))
        {      
            printf("\033[0;31mERROR :Unclosed quotes\033[0m\n");
            return ;  
        } 
}