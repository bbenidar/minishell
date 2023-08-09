/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dell_space.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 02:53:39 by bbenidar          #+#    #+#             */
/*   Updated: 2023/08/09 03:07:07 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	keep_quotes(char *line)
{
	int		i;
	int		c;

	i = 0;
	c = 0;
	while (line[i])
	{
		if ((line[i] == 34 && line[i + 1] == 34)
			|| (line[i] == 39 && line[i + 1] == 39))
		{
			c = i + 2;
			while (line[c] && line[c] == ' ')
				c++;
			if ((line[c] == '|' || line[c] == '\0'))
			{
				line[i] *= -1;
				line[i + 1] *= -1;
			}
		}
		i++;
	}
}

void	finalize_string(char *str)
{
	int	j;

	j = 0;
	while (str[j])
	{
		if (str[j] == 34 * -1 || str[j] == 39 * -1)
			str[j] *= -1;
		j++;
	}
}

char	*dell_space(char *line)
{
	int		i;
	char	*str;
	int		j;

	j = 0;
	if (!line)
		return (NULL);
	keep_quotes(line);
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
	finalize_string(str);
	return (str);
}
