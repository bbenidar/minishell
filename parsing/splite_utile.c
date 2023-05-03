/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splite_utile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 18:27:38 by bbenidar          #+#    #+#             */
/*   Updated: 2023/05/03 15:00:13 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

static int    count_wrd(char const *s)
{
    int    i;
    int    j;
    int    b;
    int r;
    int c;

    i = 0;
    r = 0;
    c = 0;
    j = 0;
    b = 0;
    while (s[b])
    {
        if ((s[b] != '|' ) && j == 0)
        {
            j = 1;
            i++;
            r = 0;
        }
        else if (s[b] == '|' && r == 0 )
        {
            r = 1;
            c++;
            j = 0;
        }
        b++;
    }
    return (i + c);
}

static int	count_split(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
	return (i);
}
static int	count_split_inv(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] == c)
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
	int r;

	i = 0;
	r = 0;
	if (!s)
		return (0);
	p = malloc(sizeof(char *) * (count_wrd(s) + 1));
	if (!p)
		return (0);
	while (*s)
	{
		while (*s && (*s == '|'))
		{
			if(r == 0)
			{
				p[i] = ft_substr(s, 0, count_split_inv(s, '|'));
				r = 1;
				i++;
			}
			s++;
		}
		if (*s)
		{
			p[i] = ft_substr(s, 0, count_split(s, '|'));
			if (!p[i])
				return (free_splits(p));
			i++;
			r = 0;
		}
		while (*s && (*s != '|'))
			s++;
	}
	p[i] = 0;
	return (p);
}