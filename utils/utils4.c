/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 13:21:25 by bbenidar          #+#    #+#             */
/*   Updated: 2023/07/29 02:43:39 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_tab(char **tab)
{
	char	**ptr;

	if (tab == NULL)
		return ;
	ptr = tab;
	while (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
		ptr++;
	}
	free(tab);
	tab = NULL;
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

static int	ft_sing(const char *str, int *hi)
{
	int	sign;
	int	i;

	i = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] == 45 || str[i] == 43)
	{
		if (str[i] == 45)
			sign *= -1;
		i++;
	}
	*hi = i;
	return (sign);
}

int	ft_atoi(const char *str)
{
	int	sign;
	int	result;
	int	i;

	result = 0;
	i = 0;
	sign = ft_sing(str, &i);
	while (str[i] && str[i] >= 48 && str[i] <= 57)
	{
		result *= 10;
		result += str[i] - 48;
		i++;
	}
	result *= sign;
	return (result);
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

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		c += 32;
	return (c);
}