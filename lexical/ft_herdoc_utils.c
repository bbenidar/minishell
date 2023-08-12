/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_herdoc_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:08:02 by bbenidar          #+#    #+#             */
/*   Updated: 2023/08/12 21:45:22 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_herd(int sig)
{
	(void)sig;
	g_flags.herdo_c = 1;
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

char	*generate_unique_filename(void)
{
	char		*her;
	char		*name;
	char		*tty;

	name = ttyname(1);
	tty = ft_strchr(name, '0');
	name = ft_itoa(generate_random_number());
	her = ft_strjoin(ft_strdup(tty), name);
	free(name);
	name = ft_strjoin(ft_strdup("/tmp/heredoc"), her);
	free(her);
	return (name);
}

int	create_herdoc_file(char **name)
{
	int	fd;

	*name = generate_unique_filename();
	fd = open(*name, O_CREAT | O_RDWR | O_TRUNC, 0777);
	return (fd);
}
