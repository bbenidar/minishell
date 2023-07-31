/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakarkal <sakarkal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 03:36:26 by sakarkal          #+#    #+#             */
/*   Updated: 2023/07/31 03:38:08 by sakarkal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_env(t_envir *a)
{
	while (a)
	{
		if (a->value != NULL)
		{
			if (!ft_strcmp(a->variable, "PATH") && flags.path_fl == 1)
				printf("");
			else
				printf("%s=%s\n", a->variable, a->value);
		}
		a = a->next;
	}
}
