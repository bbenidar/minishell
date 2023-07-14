/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execut.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 23:13:34 by bbenidar          #+#    #+#             */
/*   Updated: 2023/07/14 00:56:29 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

char *ft_getfile_name(char **cammnd, t_envir *envr)
{
    char *str = NULL;
    char **paths;
    int i = 0;
    while(envr)
    {
        
        if (!ft_strcmp(envr->variable, "PATH"))
        {
            
            str = ft_strdup(envr->value);
            break ;
        }
        envr = envr->next;
    }
// printf("hs : %s\n", cammnd[0]);
    paths = ft_split(str, ':');
    while(paths[i])
    {
        // printf("hs : %s\n", ft_strjoin(ft_strjoin(paths[i], "/"), cammnd[0]));

        if(!access(ft_strjoin(ft_strjoin(paths[i], "/"), cammnd[0]), F_OK))
            return(ft_strjoin(ft_strjoin(paths[i], "/"), cammnd[0]));
        i++;
    }
    return(NULL);

}

void ft_execution(t_last *last, char **env, t_envir *envr)
{
    pid_t pid;

    while(last)
    {
        pid = fork();
        // printf("paths : %s\n", ft_getfile_name(last->word, envr));
        if(pid == 0)
        {
            execve(ft_getfile_name(last->word, envr), last->word, env);
            return ;
        }
        
        last = last->next;
    }
    
}