/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:23:52 by sakarkal          #+#    #+#             */
/*   Updated: 2023/07/28 00:00:09 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	all_digits(char *c)
{
	int	i;

	i = 0;
	if (!c)
		return (1);
	if (c[0] == '-' || c[0] == '+')
		i++;
	while (c[i])
	{
		if (c[i] < 48 || c[i] > 57)
			return (1);
		i++;
	}
	return (0);
}

void	ft_exit(char **str)
{

	if (str[1])
	{
		if (!str[2])
		{
			if (all_digits(str[1]) == 0)
			{
				printf("exit\n");
				exit(ft_atoll(str[1]) % 256);
			}
			else
			{
				printf("exit\nminishell: exit: %s: numeric argument required", str[1]);
				exit(255);
			}
		}
		else
			printf("exit\nminishell: exit: too many arguments\n");
	}
	else
	{
		printf("exit\n");
		exit(0);
	}
}
