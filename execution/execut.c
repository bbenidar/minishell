/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execut.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 23:13:34 by bbenidar          #+#    #+#             */
/*   Updated: 2023/07/15 01:42:05 by bbenidar         ###   ########.fr       */
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
    free(str);
    while(paths[i])
    {
        // printf("hs : %s\n", ft_strjoin(ft_strjoin(paths[i], "/"), cammnd[0]));

        if(!access(ft_strjoin(ft_strjoin(paths[i], "/"), cammnd[0]), F_OK))
            return(ft_strjoin(ft_strjoin(paths[i], "/"), cammnd[0]));
        i++;
    }
    return(NULL);

}

int ft_check_for_builting(t_last *last)
{
    if(!ft_strcmp(last->word[0], "echo"))
    {
        ft_echo(last, last->word);
        exit(0);
    }
    return (0);
        
    


}

void ft_execution(t_last *last, char **env, t_envir *envr)
{
    pid_t pid;

    while(last)
    {
        pid = fork();
        
        if(pid == 0)
        {   
              if (last->input != STDIN_FILENO)
            {
                if (dup2(last->input, STDIN_FILENO) == -1)
                {
                    perror("dup2");
                    exit(1);
                }
            }
            if (last->output != STDOUT_FILENO)
            {
                if (dup2(last->output, STDOUT_FILENO) == -1)
                {
                    perror("dup2");
                    exit(1);
                }
            }
            close(last->input);
            close(last->output);
            if(!ft_getfile_name(last->word, envr))
            {
                printf("minishell : command not found\n");
                exit (1);
            }
            if(!ft_check_for_builting(last))
                execve(ft_getfile_name(last->word, envr), last->word, env);
            perror("minishell :");
            exit(1);

            
        }
        waitpid(pid, NULL, 0);
            last = last->next;
    }
    
}