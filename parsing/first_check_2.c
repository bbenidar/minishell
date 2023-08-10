/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_check_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 00:59:54 by bbenidar          #+#    #+#             */
/*   Updated: 2023/08/10 01:00:37 by bbenidar         ###   ########.fr       */
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
