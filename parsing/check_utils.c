/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 10:18:03 by bbenidar          #+#    #+#             */
/*   Updated: 2023/08/10 00:51:52 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_character(char c, char *check)
{
	while (*check)
	{
		if (c == *check)
			return (1);
		check++;
	}
	return (0);
}
