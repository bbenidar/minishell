/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 00:28:19 by bbenidar          #+#    #+#             */
/*   Updated: 2023/07/15 01:59:25 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include"../../minishell.h"

int chech_for_no_new_line(char *str)
{
    int i;
    
    i = 1;
    if(str[0] != '-')
        return (1);
    
    while(str[i])
    {
        if(str[i] != 'n')
            return(1);
        i++;
    }
    return (0);
        
}

void ft_putstr(char *str, int fd)
{
    while(*str)
    {
        write(fd, str, 1);
        str++;
    }
}

void		ft_echo(t_last *last,char **str)
{
    int i = 1;
    int flag = 1;

    if (!chech_for_no_new_line(str[1]))
        flag = 0;
    if(!flag)
        i++;
    while (str[i])
    {
        ft_putstr_fd(str[i], 1);
        write(1, " ", 1);
        i++;
    }
    if(!flag)
        write(1 , "\n", 1);
}
