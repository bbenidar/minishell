/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:55:00 by bbenidar          #+#    #+#             */
/*   Updated: 2023/08/12 21:17:32 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	ft_last_check(char *line)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		if (line[i + 1] && line[i] == '$'
			&& line[i + 1] == '\"')
			line[i] = ' ';
		i++;
	}
}

char	*ft_strchr(const char *s, int c)
{
	char	*ss;

	ss = (char *)s;
	while (*ss && *ss != (char)c)
		ss++;
	if (*ss == (char)c)
		return (ss);
	return (0);
}

t_stack	*ft_lstlast(t_stack *lst)
{
	while (lst)
	{
		if (lst -> next == NULL)
			return (lst);
		lst = lst -> next;
	}
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] == s2[i] && s1[i])
	{
		if (i < (n - 1))
			i++;
		else
			return (0);
	}
	return ((unsigned char)(s1[i]) -(unsigned char)(s2[i]));
}
