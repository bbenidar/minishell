/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakarkal <sakarkal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 18:02:31 by sakarkal          #+#    #+#             */
/*   Updated: 2023/08/06 18:02:32 by sakarkal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_env(t_envir *a, int i)
{
	if(i)
		ft_env_ex(a);
	else
	{
		while (a)
		{
			if(a->value != NULL)
			{
				if (!ft_strcmp(a->variable, "PATH")  && g_flags.path_fl == 1)
						printf("");
				else
					printf("%s=%s\n", a->variable, a->value);
			}
				
			a = a->next;
		}
	}

}
