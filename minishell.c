/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 17:17:03 by bbenidar          #+#    #+#             */
/*   Updated: 2023/08/01 00:43:50 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envir *creat_env_list()
{
	t_envir *list;

	list = malloc(sizeof(t_envir) * 1);
	list->next = NULL;
	return (list);
}

char *ft_variabl(char *str)
{
	int i = 0;
	char *ret;

	while (str[i] != '=')
		i++;
	ret = malloc(sizeof(char) * (i + 1));
	i = -1;
	while (str[++i] != '=')
	{
		ret[i] = str[i];
	}
	ret[i] = '\0';
	return (ret);
}

char *ft_value(char *str)
{
	int i = 0;
	char *ret;

	while (*str && *str != '=')
		str++;
	str++;
	while (str[i])
		i++;
	ret = malloc(sizeof(char) * (i + 1));
	i = -1;
	while (str[++i])
		ret[i] = str[i];
	ret[i] = '\0';
	return (ret);
}

t_envir *ft_no_env()
{
	char buffer[4096];
	getcwd(buffer, sizeof(buffer));
	t_envir *list;
	t_envir *ret;
	// flags.shlvl = ft_get_shlvl();
	list = creat_env_list();
	ret = list;
	list->variable = ft_strdup("PWD");
	list->equal = ft_strdup("=");
	list->value = ft_strdup(buffer);
	list->next = creat_env_list();
	list = list->next;
	list->variable = ft_strdup("SHLVL");
	list->equal = ft_strdup("=");
	list->value = ft_itoa(flags.shlvl);
	list->next = creat_env_list();
	list = list->next;
	list->variable = ft_strdup("_");
	list->equal = ft_strdup("=");
	list->value = ft_strdup("/usr/bin/env");
	list->next = creat_env_list();
	list = list->next;
	list->variable = ft_strdup("PATH");
	list->equal = ft_strdup("=");
	list->value = ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
	flags.path_fl = 1;
	

	return(ret);
	
}

t_envir *replace_variables(char **env)
{
	t_envir *list;
	t_envir *ret;
	int i;

	i = 0;
	if (env[0])
	{
		list = creat_env_list();
		ret = list;
		while (env[i])
		{
			list->variable = ft_variabl(env[i]);
			list->value = ft_value(env[i]);
			list->equal = ft_value("=");
			i++;
			if (env[i])
			{
				list->next = creat_env_list();
				list = list->next;
			}
		}
	}
	else
		ret = ft_no_env();
	return (ret);
}




void ft_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	// rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void begin(char **env)
{

	t_envir *envr;
	t_envir *tmp;
	char *line;

	signal(SIGINT, ft_sigint);
	envr = replace_variables(env);
	tmp = envr;
	printf("nb %d \n", flags.delim_flags);
	while (1337)
	{
		line = readline("➜ minishell ✗ ");
		if (!line)
		{
			printf("exit\n");
			break;
		}
		if (!check_space(line))
			add_history(line);
		
		
		if (!ft_first_check(line))
		{
			line = ft_add_variables(line, envr);
			// printf("nb %s \n", line);
			if(line)
				lexical_function(line, env, envr);
		}
		else 
			flags.exit_stat = 66048;
		free(line);
	}
}

#include <string.h>
int main(int ac, char **av, char **env)
{
	av[1] = 0;
	if (ac != 1)
		return (0);
	
	// rl_catch_signals = 0;
	printf("\033[2J\033[1;1H");
	printf("\n");
	printf("\033[0;32m███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     \n");
	printf("\033[0;32m████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     \n");
	printf("\033[0;32m██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     \n");
	printf("\033[0;32m██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     \n");
	printf("\033[0;32m██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗\n");
	printf("\033[0;32m╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n");
	printf("\033[0;32m      Made by : \033[1;91msakarkal\033[m and \033[1;91mbbenidar\033[m\n");

	begin(env);
}
