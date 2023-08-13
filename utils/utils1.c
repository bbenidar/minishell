/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 17:29:52 by bbenidar          #+#    #+#             */
/*   Updated: 2023/08/13 16:35:35 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_substr(char const *s, int start,
		int len)
{
	char	*src;
	int		i;
	int		j;

	i = 0;
	j = 0;
	src = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len >= ft_strlen(s + start))
		len = ft_strlen(s + start);
	src = (char *)malloc(sizeof(char) * (len + 1));
	if (!src)
		return (0);
	while (s[i])
	{
		if (i >= start && len > j)
			src[j++] = s[i];
		i++;
	}
	src[j] = 0;
	return (src);
}

int	count_wrd(char const *s, char c)
{
	int	i;
	int	j;
	int	b;

	i = 0;
	j = 0;
	b = 0;
	while (s[b])
	{
		if (s[b] != c && j == 0)
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

char	**ft_split(char const *s, char c)
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
