/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execut.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakarkal <sakarkal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 23:13:34 by bbenidar          #+#    #+#             */
/*   Updated: 2023/07/18 11:53:47 by sakarkal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int ft_strchr(char *s, int c)
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

	if (ft_strchr(cammnd[0], '/') == 1)
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
	if (!ft_strcmp(last->word[0], "echo"))
	{
		ft_echo(last, last->word);
		return (1);
	}
	if (!ft_strcmp(last->word[0], "cd"))
	{
		ft_cd(last->word[1], env);
		return (1);
	}
	if (!ft_strcmp(last->word[0], "env"))
	{
		ft_env(env);
		return (1);
	}
	if (!ft_strcmp(last->word[0], "export"))
	{
		ft_export(env, last->word);
		return (1);
	}
	if (!ft_strcmp(last->word[0], "pwd"))
	{
		ft_pwd();
		return (1);
	}
	if (!ft_strcmp(last->word[0], "exit"))
	{
		ft_exit();
		return (1);
	}
	if(!ft_strcmp(last->word[0], "unset"))
    {
        i = 0;
        while(last->word[++i])
        ft_unset(env, last->word[i]);
        return (1);
    }
	return (0);
}

void ft_execution(t_last *last, char **env, t_envir *envr)
{
	pid_t pid;

    char **envire;
    while (last) {
        if (ft_check_for_builting(last, envr)) {
            last = last->next;
            envire = ft_merge_envr(envr);
        } else {
            pid = fork();
            if (pid == 0) {
                if (last->input != STDIN_FILENO) {
                    if (dup2(last->input, STDIN_FILENO) == -1) {
                        perror("dup2");
                        exit(1);
                    }
                }
                if (last->output != STDOUT_FILENO) {
                    if (dup2(last->output, STDOUT_FILENO) == -1) {
                        perror("dup2");
                        exit(1);
                    }
                }
                char *path = ft_getfile_name(last->word, envr);
                if (!path) 
				{
                    printf("minishell: command not found: %s\n", last->word[0]);
                    exit(1);
                }
                envire = ft_merge_envr(envr);
                execve(path, last->word, envire);
                perror("minishell");
                exit(1);
            } else if (pid < 0) {
                perror("fork");
                exit(1);
            } else {
                waitpid(pid, NULL, 0);
                last = last->next;
            }
        }
    }
}