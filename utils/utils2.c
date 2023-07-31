/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 18:20:07 by bbenidar          #+#    #+#             */
/*   Updated: 2023/07/07 13:37:12 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

t_stack	*ft_new_node(void)
{
	t_stack	*begin;

	begin = (t_stack *)malloc(sizeof(t_stack));
	if (!begin)
		return (NULL);
	begin->word = 0;
	begin->key = -1;
	begin->next = NULL;
	return (begin);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_strlen_no_null(const char *str)
{
	int	i;

	i = 0;
	if(!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	size_t	i;
	size_t	len;
	char	*p;

	i = 0;
	len = ft_strlen(s1);
	p = (char *)malloc(sizeof(char) * len + 1);
	if (!p)
		return (NULL);
	while (i <= len)
	{
		p[i] = s1[i];
		i++;
	}
	return (p);
}

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
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