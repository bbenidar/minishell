/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakarkal <sakarkal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 06:24:27 by sakarkal          #+#    #+#             */
/*   Updated: 2023/08/09 06:25:34 by sakarkal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	chech_for_no_new_line(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-')
		return (1);
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

void	ft_putstr(char *str, int fd)
{
	while (*str)
		write(fd, str, 1);
	{
		str++;
	}
}

void	ft_echo(t_last *last, char **str)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (!str[1])
		write(last->output, "\n", 1);
	else 
	{
		while (!chech_for_no_new_line(str[i]))
		{
			flag = 1;
			i++;
		}
		while (str[i])
		{
			ft_putstr_fd(str[i], last->output);
			if (str[i + 1] != 0)
				write(last->output, " ", 1);
			i++;
		}
		if (!flag)
			write(last->output, "\n", 1);
	}
}
