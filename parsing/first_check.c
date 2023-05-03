/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 13:26:45 by bbenidar          #+#    #+#             */
/*   Updated: 2023/05/03 18:20:01 by bbenidar         ###   ########.fr       */
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

static int ft_skip_qoutes(char *str)
{
    int i;
    char c;

    c = *str;
    if (c != 34 || c != 39)
        return (0);
    i = 1;
    while(str[i] && str[i] != c)
        i++;  
    return (i);    
}

static int check_pipe(char *str)
{
    while(*str)
    {
        if((*str == 124 && *(str + 1) != 124))
        {
            str++;
            while(*str == 32)
                str++;
            if (!*str || *str == 124 || *str == 38)
                return (1);  
        }
        str += ft_skip_qoutes(str);
        if (*str)
            str++;     
    }
    return (0);
}

int check_logical(char *str)
{
    while(*str)
    {
        if(*str == 38  || *str == 124 )
        {    
            str ++;
            if (*str == 38)
                return (1);
            while(*str == 32)
                str++;
            if(check_character(*str, "<>|")) //hna mhtaj function tchiki liya yak makayn ("<>|")!
                return (1);
            
        }
        if(*str)
            str++;
    }
    return (0);
}

int ft_first_check(char *str)
{
    while(*str == ' ')
        str++;
    if(check_space(str))
         return (1);  
    if (ft_check_quotes(str))   
        printf("\033[0;31mERROR :Unclosed quotes\033[0m\n"); 
    else if (*str == 124 || check_pipe(str))
        printf("\033[0;31mminishell: parse error near `|`\033[0m\n");
    else if (check_logical(str))
        printf("\033[0;31mminishell: LOGICAL ERROR (logic operation not handled)\033[0m\n\n");
    else
        return (0);
    return(1);   
}
