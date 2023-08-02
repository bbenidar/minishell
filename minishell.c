/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 17:17:03 by bbenidar          #+#    #+#             */
/*   Updated: 2023/08/02 18:32:48 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envir	*creat_env_list(void)
{
	t_envir	*list;

	list = malloc(sizeof(t_envir) * 1);
	list->next = NULL;
	return (list);
}

void	ft_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	// rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

int	ft_checker(char *line)
{
	if (!line)
	{
		printf("exit\n");
		return (0);
	}
	return (1);
}

void	begin(char **env)
{
	t_envir	*envr;
	t_envir	*tmp;
	char	*line;

	signal(SIGINT, ft_sigint);
	envr = replace_variables(env, 0);
	tmp = envr;
	while (1337)
	{
		line = readline("➜ minishell ✗ ");
		if (!ft_checker(line))
			break ;
		if (!check_space(line))
			add_history(line);
		if (!ft_first_check(line))
		{
			line = ft_add_variables(line, envr);
			printf("LINE : %s\n", line);
			if (line)
				lexical_function(line, env, envr);
		}
		else 
			g_flags.exit_stat = 66048;
		free(line);
	}
}

int	main(int ac, char **av, char **env)
{
	av[1] = 0;
	if (ac != 1)
		return (0);
	// rl_catch_signals = 0;
	printf("\033[2J\033[1;1H");
	printf("\n");
	printf("\033[0;32m      Made by : \033[1;91m");
	printf("sakarkal\033[m and \033[1;91mbbenidar\033[m\n");
	begin(env);
}
