/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 13:26:45 by bbenidar          #+#    #+#             */
/*   Updated: 2023/04/30 15:32:51 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

static int check_space(char *str)
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
    {  
        printf("ERROR");
         exit(1);  
    }
    if (ft_check_qouts(str))
        
    
     
    
}