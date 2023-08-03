/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:33:37 by bbenidar          #+#    #+#             */
/*   Updated: 2023/08/03 17:49:50 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_intlen(int n)
{
	int	i;

	i = 1;
	if (n == -2147483648)
		return (11);
	else
	{
		if (n < 0)
		{
			n = n * -1;
			i++;
		}
		while (n > 9)
		{
			n = n / 10;
			i++;
		}
		return (i);
	}
}

static int	sign(char *p, int n)
{
	int	i;

	i = 0;
	if (n == -2147483648)
	{
		p[i] = '-';
		p[++i] = '2';
		n = 147483648;
	}
	if (n < 0)
	{
		p[i] = '-';
		n = n * -1;
	}
	return (n);
}

char	*ft_itoa(unsigned int n)
{
	char	*p;
	int		i;
	int		len;

	i = 0;
	len = ft_intlen(n);
	p = (char *)malloc(sizeof(*p) * (len + 1));
	if (!p)
		return (0);
	if(g_flags.col)
	{
		g_flags.col->next = ft_get_new_node();
		g_flags.col = g_flags.col->next;
	}
	else
		g_flags.col = ft_get_new_node();
	g_flags.col->collecter = p;
	p[len] = '\0';
	n = sign(p, n);
	while (n > 9)
	{
		p[len - 1] = (n % 10) + '0';
		len--;
		n = n / 10;
	}
	if (n <= 9)
		p[len - 1] = n + '0';
	return (p);
}
