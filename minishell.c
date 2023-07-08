/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 17:17:03 by bbenidar          #+#    #+#             */
/*   Updated: 2023/07/08 13:36:55 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void begin()
{
    char *line;
    while(1337)
    {
        line = readline("➜ minishell ✗ ");
        if(!line)
        {
            printf("EXITE");
            break;
        }
        // printf("line : |%lu|\n", strlen(line));
        if (!check_space(line))
            add_history(line);
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
    printf("\033[2J\033[1;1H");
    printf("\n");
    printf("\033[0;32m███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     \n");
    printf("\033[0;32m████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     \n");
    printf("\033[0;32m██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     \n");
    printf("\033[0;32m██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     \n");
    printf("\033[0;32m██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗\n");
    printf("\033[0;32m╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n");
    printf("\033[0;32m      Made by : \033[1;91sakarkal\033[m and \033[1;91mbbenidar\033[m\n");

    begin();
}
