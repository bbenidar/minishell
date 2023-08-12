/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_herdoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 20:55:36 by bbenidar          #+#    #+#             */
/*   Updated: 2023/08/12 21:44:38 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	generate_random_number(void)
{
	static int	rand_num;

	return (rand_num++);
}

static void	setup_herdoc_environment(t_stack *list)
{
	char	*word_without_quotes;

	if (list->next && (!ft_strcmp(list->next->word, "\"\"")
			|| !ft_strcmp(list->next->word, "\'\'")))
	{
		free(list->next->word);
		list->next->word = ft_strdup("");
	}
	word_without_quotes = dell_qots(list->next->word);
	free(list->next->word);
	list->next->word = word_without_quotes;
}

static int	process_and_write_input(char *her, t_stack *list)
{
	if (!her)
		return (0);
	if (!ft_strlen(her) && !list->next)
		return (0);
	else if (list->next) 
	{
		return_space_to_real_value(list->next->word);
		if (!ft_strcmp(her, list->next->word))
		{
			free(her);
			return (0);
		}
	}
	return (1);
}

static void	process_herdoc_input(int fd, t_stack *list, t_envir *envr)
{
	char	*her;

	signal(SIGINT, ft_herd);
	while (isatty(STDIN_FILENO))
	{
		her = readline("> ");
		if (!process_and_write_input(her, list))
			break ;
		if (g_flags.delim_flags == 0)
			if (*her)
				her = ft_add_variables(her, envr, 1);
		ft_putstr_fd(her, fd);
		ft_putstr_fd("\n", fd);
		free(her);
	}
	if (g_flags.delim_flags != 0)
		g_flags.delim_flags--;
	signal(SIGINT, ft_sigint);
}

int	ft_herdoc(t_stack *list, t_envir *envr)
{
	int			fd;
	char		*name;

	name = NULL;
	fd = create_herdoc_file(&name);
	setup_herdoc_environment(list);
	process_herdoc_input(fd, list, envr);
	if (!isatty(STDIN_FILENO))
		return (free(name), fd_herdoc(&fd), -5);
	free(list->word);
	list->word = ft_strdup("");
	if (list->next && list->next->next && list->next->next->key == COMMAND)
	{
		free(list->word);
		list->word = list->next->next->word;
		list->key = COMMAND;
		list->next->next->word = ft_strdup("");
	}
	if (list->next)
	{
		free(list->next->word);
		list->next->word = ft_strdup(name);
		list->next->key = FILE_IN;
	}
	return (free(name), fd);
}
