/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 17:17:03 by bbenidar          #+#    #+#             */
/*   Updated: 2023/08/15 16:12:36 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envir	*creat_env_list(void)
{
	t_envir	*list;

	list = malloc(sizeof(t_envir) * 1);
	if (!list)
		return (NULL);
	list->equal = NULL;
	list->value = NULL;
	list->variable = NULL;
	list->next = NULL;
	return (list);
}

void	ft_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	if (g_flags.exit_flags != 130 * 256)
		g_flags.exit_stat = 1 * 256;
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
	char	*line;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_sigint);
	envr = replace_variables(env, 0);
	while (1337)
	{
		line = readline("➜ minishell ✗ ");
		if (!line)
			return (printf("exit\n"), exit(0));
		if (!check_space(line))
			add_history(line);
		if (!ft_first_check(line))
		{
			line = ft_add_variables(line, envr, 0);
			if (line)
				lexical_function(line, &envr);
		}
		else
			g_flags.exit_stat = 66048;
		free(line);
		g_flags.herdo_c = 0;
	}
}

int	main(int ac, char **av, char **env)
{
	av[1] = 0;
	if (ac != 1)
		return (ft_putstr_fd("HOPLAAA, args are not allowed 🤡\n", 2), 1);
	rl_catch_signals = 0;
	g_flags.qts_flgs = 1;
	printf("\033[2J\033[1;1H");
	printf("\n");
	printf("\033[0;32m      Made by : \033[1;91m");
	printf("bbenidar\033[m and \033[1;91msakarkal\033[m\n");
	begin(env);
}
