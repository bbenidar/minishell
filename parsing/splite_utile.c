/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splite_utile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 18:27:38 by bbenidar          #+#    #+#             */
/*   Updated: 2023/05/02 18:29:46 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

static int	count_wrd(char const *s)
{
	int	i;
	int	j;
	int	b;

	i = 0;
	j = 0;
	b = 0;
	while (s[b])
	{
		if ((s[b] != '|' || s[b] != '&') && j == 0)
		{
			j = 1;
			i++;
		}
		else if (s[b] == c)
			j = 0;
		b++;
	}
	return (i);
}

static int	count_split(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
	return (i);
}

static char	**free_splits(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (split);
}

char	**ft_split_opera(char const *s)
{
	char	**p;
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	p = malloc(sizeof(char *) * (count_wrd(s, c) + 1));
	if (!p)
		return (0);
	while (*s)
	{
		while (*s && (*s == c))
			s++;
		if (*s)
		{
			p[i] = ft_substr(s, 0, count_split(s, c));
			if (!p[i])
				return (free_splits(p));
			i++;
		}
		while (*s && (*s != c))
			s++;
	}
	p[i] = 0;
	return (p);
}