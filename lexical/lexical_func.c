/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 11:39:12 by bbenidar          #+#    #+#             */
/*   Updated: 2023/05/01 16:02:28 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void lexical_function(char *line)
{
    t_stack wrd;
    int i;
    int j;
    i = 0;
    j = 0;
    
    while(line[i])
    {
        if(ft_isalpha(line[i]))
            {
                while(ft_isalpha(line[i]))
                {
                    ft_strjoin();
                }
            }
    }
}