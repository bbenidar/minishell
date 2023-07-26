/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execut.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:24:13 by sakarkal          #+#    #+#             */
/*   Updated: 2023/07/26 22:14:59 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int ft_strchr_sla(char *s, int c)
{
	int i;

	i = -1;
	while (s[++i])
		if (s[i] == (unsigned char)c)
			return (1);
	return (0);
}

char *ft_getfile_name(char **cammnd, t_envir *envr)
{
	char *str = NULL;
	char **paths;
	int i = 0;

	if (ft_strchr_sla(cammnd[0], '/') == 1)
	{
		return (cammnd[0]);
	}

	while (envr)
	{

		if (!ft_strcmp(envr->variable, "PATH"))
		{

			str = ft_strdup(envr->value);
			break;
		}
		envr = envr->next;
	}
	paths = ft_split(str, ':');
	free(str);
	while (paths[i])
	{
		if (!access(ft_strjoin(ft_strjoin(paths[i], "/"), cammnd[0]), F_OK))
			return (ft_strjoin(ft_strjoin(paths[i], "/"), cammnd[0]));
		i++;
	}
	return (NULL);
}

int ft_check_for_builting(t_last *last, t_envir *env)
{
	int i;
    if(last->word[0])
    {
        if (!ft_strcmp(last->word[0], "echo"))
        {
            ft_echo(last, last->word);
            return (1);
        }
        else if (!ft_strcmp(last->word[0], "cd"))
        {
            ft_cd(last->word[1], env);
            return (1);
        }
        else if (!ft_strcmp(last->word[0], "env"))
        {
            ft_env(env);
            return (1);
        }
        else if (!ft_strcmp(last->word[0], "export"))
        {
            printf("HHHH\n");
            ft_export(env, last->word);
            return (1);
        }
        else if (!ft_strcmp(last->word[0], "pwd"))
        {
            ft_pwd();
            return (1);
        }
        else if (!ft_strcmp(last->word[0], "exit"))
        {
            ft_exit(last->word);
            return (1);
        }
        else if(!ft_strcmp(last->word[0], "unset"))
        {
            i = 0;
            while(last->word[++i])
            ft_unset(env, last->word[i]);
            return (1);
        }
    }
   
	
	return (0);
}

void close_pipe(int pipe_fds[2]) {
    close(pipe_fds[0]);
    close(pipe_fds[1]);
}

void ret_toreal_v(char **str)
{
    int i;

    i = 0;
    while(str[i])
    {
        return_space_to_real_value(str[i]);
        i++;
    }
}

void ft_execution(t_last *last, char **env, t_envir *envr) {
    int prev_pipe_read = STDIN_FILENO;
    char **envire; // Read end of the previous pipe

    envire = env;
    while (last) {
        ret_toreal_v(last->word);
    //    printf("cmnd : %s fd-out : %d fd-in : %d\n", last->word[0], last->output, last->input );

            envire = ft_merge_envr(envr);
            int pipe_fds[2];

            if (last->next) {
                if (pipe(pipe_fds) == -1) {
                    perror("pipe");
                    exit(0);
                }
            }

            pid_t pid = fork();
            if (pid == 0) {
                // Child process
                if (prev_pipe_read != STDIN_FILENO) {
                    if (dup2(prev_pipe_read, STDIN_FILENO) == -1) {
                        perror("dup2");
                        exit(0);
                    }
                    close(prev_pipe_read);
                }

                if (last->next) {
                    if (dup2(pipe_fds[1], STDOUT_FILENO) == -1) {
                        perror("dup2");
                        exit(0);
                    }
                    close(pipe_fds[1]);
                }

                close_pipe(pipe_fds);

                
                 if (last && last->output != -1) {
            int output_fd = last->output;
            if (dup2(output_fd, STDOUT_FILENO) == -1) {
                perror("dup2");
                exit(0);
            }
        }
         if (last && last->input != -1) {
            int input_fd = last->input;
            if (dup2(input_fd, STDIN_FILENO) == -1) {
                perror("dup2");
                exit(0);
            }
        }
                // printf("\033[1;91msakarkal\033[m\n");
                // for (int h = 0; envire[h]; h++)
                //     printf("\033[1;91m | %s |\033[m\n", envire[h]);
                if (ft_check_for_builting(last, envr)) 
                {
                    exit(1);
                } 
                else{
                    char *path = ft_getfile_name(last->word, envr);
                if (!path) {
                    printf("minishell: command not found: %s\n", last->word[0]);
                    exit(0);
                }
                    execve(path, last->word, envire);
                        perror("minishell");
                        exit(0);
                }
                
            } else if (pid < 0) {
                perror("fork");
                exit(0);
            } else {
                // Parent process
                if (prev_pipe_read != STDIN_FILENO) {
                    close(prev_pipe_read);
                }

                if (last->next) {
                    close(pipe_fds[1]);
                }

                prev_pipe_read = pipe_fds[0]; // Store the read end of the current pipe for the next iteration

                last = last->next;
            }

        // Handle output redirection
       
    }
    while (wait(&exit_stat) > 0)
        ;
    // printf("ex : %d\n", exit_stat/256);
}