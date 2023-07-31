/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoll.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakarkal <sakarkal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 06:30:29 by sakarkal          #+#    #+#             */
/*   Updated: 2023/07/31 07:00:52 by sakarkal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_ovf(unsigned long long before, unsigned long long r, int neg)
{
	if (before < r && (r == (-9223372036854775807ULL - 1LL) && neg == 1))
		return (0);
	if ((before < r && r > LLONG_MAX) && (neg == -1 || neg == 1))
		return (ft_putendl_fd("minishell: exit: numeric \
					argument required hiya", 2), 255);
	return (-1);
}

static long long	ft_sing(const char *str, long long *hi)
{
	long long	sign;
	long long	i;

	i = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] == 45 || str[i] == 43)
	{
		if (str[i] == 45)
		{
			sign = -1;
		}
		i++;
	}
	*hi = i;
	return (sign);
}

long long	ft_atoll(char *str)
{
	long long	sign;
	long long	result;
	long long	before;
	long long	ovrflw;
	long long	i;

	result = 0;
	ovrflw = 0;
	i = 0;
	sign = ft_sing(str, &i);
	while (str[i] && str[i] >= 48 && str[i] <= 57)
	{
		result *= 10;
		result += str[i] - 48;
		ovrflw = check_ovf(before, result, sign);
		if (ovrflw != -1)
			return (ovrflw);
		before = result;
		i++;
	}
	result *= sign;
	return (result);
}
