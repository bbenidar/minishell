/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 14:22:09 by bbenidar          #+#    #+#             */
/*   Updated: 2023/07/15 16:28:32 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../minishell.h"


char *get_logine(t_envir *env)
{
    while(env)
    {
        if (!ft_strcmp(env->variable , "USER"))
            return (ft_strdup(env->value));
        env = env->next;
    }
    return (NULL);
}

char *get_path(t_envir *env)
{
    while(env)
    {
        if (!ft_strcmp(env->variable , "OLDPWD"))
            return (ft_strdup(env->value));
        env = env->next;
    }
    return (NULL);
}

void	ft_cd(char *arg, t_envir *env)
{
    char *login;
    char *path;
    char buffer[4096];

    // buffer = malloc(4096);
    // if(!buffer)
    //     perror("minishell");
    if(getcwd(buffer, sizeof(buffer)) != NULL)
    {
        path = get_path(env);
            login = get_logine(env);
            // printf("arg : %s | path : %s\n", buffer, ft_strjoin("/", arg));
            if (!arg)
            {   
                chdir(ft_strjoin("/Users/", login));
                    // perror("minishell");
            }
        
           chdir(ft_strjoin(ft_strjoin(buffer, "/"), arg));
                // perror("minishell");

    }
    
    // free(buffer);
}

