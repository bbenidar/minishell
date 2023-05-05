/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 11:39:12 by bbenidar          #+#    #+#             */
/*   Updated: 2023/05/05 20:38:00 by bbenidar         ###   ########.fr       */
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
        if( str[i] != 34 && str[i] != 39)
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
        if(line[j] != 34 && line[j] != 39)
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
    // char *final;
    char **src;
    int i;
    // int j;
    i = 0;
    
    
    str = dell_space(line);
    printf("str : %s\n", str);
    // final = dell_opera(str);
    src = ft_split_opera(str);
    
    while(src[i])
    {
        // j = 0;
        // while(src[i][j])
        // {
        //     while (src[i][j] == ' ' || src[i][j] == )
        // }
        printf("src : %s\n", src[i]);
        i++;
    }   
}


//  int ft_strlen_no_q(char *str)
//  {
//     int i;
//     int j;

//     i = 0;
//     j = 0;

//     while(str[i])
//     {
//         if(str[i] == 34 || str[i] == 39)
//             j++;
//         i++;
//     }
//     return (j);
//  } 
 
//  char *dell_qoates(char *str)
//  {
//     int i;
//     char *src;

//     i = ft_strlen_no_q(str);
//     src = maloc
//  }