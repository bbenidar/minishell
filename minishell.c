/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 17:17:03 by bbenidar          #+#    #+#             */
/*   Updated: 2023/05/03 17:50:06 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void begin()
{
    char *line;
    while(42)
    {
        line = readline("\033[0;33m➜ minishell ✗ \033[0m");
        if(!line)
        {
            printf("EXITE");
            break;
        }
        if (!check_space(line))
            add_history(line);
        // if(line && *line && !
        if(!ft_first_check(line))
            lexical_function(line); 
        
    }
}

#include <string.h>
int main(int ac, char **av)
{
    av[1] = 0;
    if (ac != 1)
        return (0);
    printf("\033[0;32m/* ************************************************************************** */\n");
    printf("\033[0;32m/*                                                                            */\n");
    printf("\033[0;32m/*                                                        :::      ::::::::   */\n");
    printf("\033[0;32m/*   MINISHELL                                          :+:      :+:    :+:   */\n");
    printf("\033[0;32m/*                                                    +:+ +:+         +:+     */\n");
    printf("\033[0;32m/*   By:\033[0;36m bbenidar && messoufi  \033[0;32m                     +#+  +:+       +#+        */\n");
    printf("\033[0;32m/*                                                +#+#+#+#+#+   +#+           */\n");
    printf("\033[0;32m/*                                                     #+#    #+#             */\n");
    printf("\033[0;32m/*                                                    ###   ########          */\n");
    printf("\033[0;32m/*                                                                            */\n");
    printf("\033[0;32m/* ************************************************************************** */\n");

    begin();
}
