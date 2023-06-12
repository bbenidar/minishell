/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:13:23 by messoufi          #+#    #+#             */
/*   Updated: 2023/06/01 19:29:13 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_newline(char *arg)
{
	if (arg != NULL && arg[0] == '-' && arg[1] == 'n' && arg[2] == '\0')
	{
		return (true);
	}
	return (false);
}

int	ft_echo(char **arg)
{
	int	nbr;
	int	i;

	nbr = false;
	i = -1;
	while (ft_newline(arg[++i]))
		nbr = true;
	while (arg[i])
	{
		printf("%s", arg[i]);
		if (arg[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (nbr == false)
		printf("\n");
	return (0);
}
