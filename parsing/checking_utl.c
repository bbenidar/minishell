/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_utl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakarkal <sakarkal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 10:38:29 by sakarkal          #+#    #+#             */
/*   Updated: 2023/08/10 10:38:30 by sakarkal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_quotes(char *str)
{
	int	a;
	int	b;
	int	i;

	a = -1;
	i = 0;
	b = -1;
	while (str && str[i])
	{
		if (str[i] == 34 && b == -1)
			a *= -1;
		if (str[i] == '$' && b != -1 && a == -1)
			str[i] *= -1;
		if (str[i] == 39 && a == -1)
			b *= -1;
		if ((str[i] == ' ' || str[i] == '<' ) && (a != -1 || b != -1))
			str[i] *= -1;
		if ((str[i] == '\'' && a != -1 && b == 1) 
			|| (str[i] == '\"' && b != -1 && a == 1))
			str[i] *= -1;
		i++;
	}
	if (a == 1 || b == 1)
		return (1);
	return (0);
}

int	check_space(char *str)
{
	if (str)
	{
		while (str && (*str == ' ' || *str == '\t'))
			str++;
		if (!*str)
			return (1);
	}
	return (0);
}

int	ft_skip_qoutes(char *str)
{
	int		i;
	char	c;

	c = *str;
	if (c != 34 && c != 39)
		return (0);
	i = 1;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}
