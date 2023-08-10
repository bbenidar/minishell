/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 18:20:07 by bbenidar          #+#    #+#             */
/*   Updated: 2023/08/09 22:51:07 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	if (!str)
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

	len = ft_strlen(s1);
	i = 0;
	p = (char *)malloc(sizeof(char) * (len + 1));
	if (!p)
		return (NULL);
	while (i < len)
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}
