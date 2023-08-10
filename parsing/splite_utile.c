/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splite_utile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 18:27:38 by bbenidar          #+#    #+#             */
/*   Updated: 2023/08/10 00:43:55 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_wrd(char const *s, char h)
{
	int	i;
	int	b;

	i = 0;
	g_flags.r_falg = 0;
	g_flags.c_falg = 0;
	g_flags.j_falg = 0;
	b = 0;
	while (s[b])
	{
		if ((s[b] != h) && g_flags.j_falg == 0)
		{
			g_flags.j_falg = 1;
			i++;
			g_flags.r_falg = 0;
		}
		else if (s[b] == h && g_flags.r_falg == 0)
		{
			g_flags.r_falg = 1;
			g_flags.c_falg++;
			g_flags.j_falg = 0;
		}
		b++;
	}
	return (i + g_flags.c_falg);
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

size_t	split_loop(char *s, char h, char **p, int *r)
{
	while (*s)
	{
		while (*s && (*s == h))
		{
			if (*r == 0)
			{
				p[g_flags.i_splt_falg] = ft_substr(s, 0, count_split_inv(s, h));
				*r = 1;
				g_flags.i_splt_falg++;
			}
			s++;
		}
		if (*s)
		{
			p[g_flags.i_splt_falg] = ft_substr(s, 0, count_split(s, h));
			if (!p[g_flags.i_splt_falg])
				return (g_flags.i_splt_falg);
			g_flags.i_splt_falg++;
			*r = 0;
		}
		while (*s && (*s != h))
			s++;
	}
	return (g_flags.i_splt_falg);
}

char	**ft_split_opera(char *s, char h)
{
	char	**p;
	size_t	i;
	int		r;

	i = 0;
	r = 0;
	g_flags.i_splt_falg = 0;
	if (!s)
		return (0);
	p = malloc(sizeof(char *) * (count_wrd(s, h) + 1));
	if (!p)
		return (0);
	i = split_loop(s, h, p, &r);
	p[i] = 0;
	return (p);
}
