/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 22:39:50 by bbenidar          #+#    #+#             */
/*   Updated: 2023/08/16 15:59:02 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*merge_tab(char **str)
{
	int		i;
	char	*line;

	i = 1;
	if (!str)
		return (NULL);
	if (str && str[0] && !str[1])
		return (ft_strdup(str[0]));
	line = ft_strdup("");
	line = ft_strjoin(line, str[0]);
	while (str && str[i])
	{
		line = ft_strjoin(line, str[i]);
		i++;
	}
	return (line);
}

void	ft_free_stack(t_stack **env)
{
	while (*env)
	{
		free((*env)->word);
		free((*env));
		(*env) = (*env)->next;
	}
}

void	ft_free_last(t_last **env)
{
	while (*env)
	{
		if ((*env)->input != 0)
			close((*env)->input);
		if ((*env)->output != 1)
			close((*env)->output);
		free_tab((*env)->word);
		free((*env));
		(*env) = (*env)->next;
	}
}

int	open_fd_out(char *word, int key)
{
	int	fd;

	if (key == FILE_APP)
		fd = open(word, O_CREAT | O_RDWR | O_APPEND, 0777);
	else
		fd = open(word, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (fd < 0)
	{
		return (fd);
	}
	return (fd);
}

char	*split_for_lexical(char *line)
{
	char	*str;
	char	**src;

	str = dell_space(line);
	src = ft_split_opera(str, '|');
	free(str);
	str = merge_str(src);
	free_tab(src);
	src = ft_split(str, '\t');
	free(str);
	str = merge_str(src);
	free_tab(src);
	src = ft_split_opera(str, '>');
	free(str);
	str = merge_str(src);
	free_tab(src);
	src = ft_split_opera(str, '<');
	free(str);
	str = merge_str(src);
	free_tab(src);
	return (str);
}
