/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_herdoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 20:55:36 by bbenidar          #+#    #+#             */
/*   Updated: 2023/08/07 21:35:08 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_herd(int sig)
{
	(void)sig;
	close(STDIN_FILENO);
}

void	fd_herdoc(int fd[2])
{
	int	fdd;

	fdd = open(ttyname(STDERR_FILENO), O_RDONLY);
	if (fdd == -1)
		return (close_pipe(fd), ft_putendl_fd("Error herdoc_fd", 2));
	close_pipe(fd);
}

int	ft_strlen_nospace(const char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] != 34 && str[i] != 39)
			j++;
		i++;
	}
	return (j);
}

char	*dell_qots(char *line)
{
	int		i;
	char	*str;
	int		j;

	j = 0;
	i = 0;
	if (!line)
		return (NULL);
	i = ft_strlen_nospace(line);
	str = (char *)malloc(sizeof(char) * i + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (line[j])
	{
		if (line[j] != 34 && line[j] != 39)
		{
			str[i] = line[j];
			i++;
		}
		j++;
	}
	str[i] = '\0';
	return (str);
}

int	ft_herdoc(t_stack *list, int flag, t_envir *envr)
{
	int			fd;
	static int	rand;
	char		*her;
	char		*name;
	char		*tty;

	name = ttyname(1);
	tty = ft_strchr(name, '0');
	name = ft_itoa(rand++);
	her = ft_strjoin(ft_strdup(tty), name);
	free(name);
	name = ft_strjoin(ft_strdup("/tmp/heredoc"), her);
	fd = open(name, O_CREAT | O_RDWR | O_TRUNC, 0777);
	free(her);
	if (list->next && (!ft_strcmp(list->next->word, "\"\"")
			|| !ft_strcmp(list->next->word, "\'\'")))
	{
		free(list->next->word);
		list->next->word = ft_strdup("");
	}
	signal(SIGINT, ft_herd);
	tty = dell_qots(list->next->word);
	free(list->next->word);
	list->next->word = tty;
	while (isatty(STDIN_FILENO))
	{
		her = readline("> ");
		if (!her)
		{
			break ;
		}
		if (!ft_strlen(her) && !list->next)
			break ;
		else if (list->next)
		{
			return_space_to_real_value(list->next->word);
			if (!ft_strcmp(her, list->next->word))
			{
				free(her);
				break ;
			}
		}
		if (g_flags.delim_flags == 0)
			her = ft_add_variables(her, envr, 1);
		ft_putstr_fd(her, fd);
		ft_putstr_fd("\n", fd);
		free(her);
	}
	if (g_flags.delim_flags != 0)
		g_flags.delim_flags--;
	signal(SIGINT, ft_sigint);
	if (!isatty(STDIN_FILENO))
		return (free(her), free(name), fd_herdoc(&fd), -5);
    free(list->word);
    list->word = ft_strdup("");
	if (list->next && list->next->next)
	{
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
	free(name);
	return (fd);
}
