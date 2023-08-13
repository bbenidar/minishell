/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_check_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 00:59:54 by bbenidar          #+#    #+#             */
/*   Updated: 2023/08/13 16:23:55 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_check_qu_helper(char *str, int i, int *a, int *b)
{
	if (str[i] == 34 && *b == -1)
		*a *= -1;
	if (((str[i] == '$') || (str[i] == '>')
			|| (str[i] == '<')) && *b != -1 && *a == -1)
		str[i] *= -1;
	if (((str[i] == '>') || (str[i] == '<')) && *b == -1 && *a != -1)
		str[i] *= -1;
	if ((str[i] == '\'') && *b == -1 && *a != -1)
		str[i] *= -2;
	if ((str[i] == '\"') && *b != -1 && *a == -1)
		str[i] *= -2;
	if (str[i] == 39 && *a == -1)
		*b *= -1;
	if ((str[i] == ' ' || str[i] == '<'
			|| str[i] == '\t') && (*a != -1 || *b != -1))
		str[i] *= -1;
	if ((str[i] == '\'' && *a != -1 && *b == 1)
		|| (str[i] == '\"' && *b != -1 && *a == 1))
		str[i] *= -1;
	if ((str[i] == '|' && *a == 1 && *b == -1)
		|| (str[i] == '|' && *b == 1 && *a == -1))
		str[i] *= -1;
}

int	ft_check_quotes(char *str)
{
	int	a;
	int	b;
	int	i;

	a = -1;
	i = -1;
	b = -1;
	while (str && str[++i])
		ft_check_qu_helper(str, i, &a, &b);
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
