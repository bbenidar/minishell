/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 11:39:12 by bbenidar          #+#    #+#             */
/*   Updated: 2023/05/03 15:29:57 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

static int	ft_strlen_nospace(const char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
    {
        if(str[i] != ' ')
            j++;
        i++;
    }
		
	return (j);
}

char *dell_space(char *line)
{
    int i;
    char *str;
    int j;
    
    j = 0;
    i = ft_strlen_nospace(line);
    str = (char *)malloc(sizeof(char) * i);
    i = 0;
    while(line[j])
    {
        if(line[j] != ' ')
        {
            str[i] = line[j];
            i++;
        }
        j++;
    }
    str[i] = '\0';
    return (str);
}
void lexical_function(char *line)
{
    // t_stack wrd;
    char *str;
    char **src;
    int i;
    // int j;
    i = 0;
    // j = 0;
    
    str = dell_space(line);
    src = ft_split_opera(line);
    
    while(src[i])
    {
        printf("src : %s\n", src[i]);
        i++;
    }   
}