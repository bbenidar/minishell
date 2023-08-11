/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 06:25:40 by sakarkal          #+#    #+#             */
/*   Updated: 2023/08/11 20:11:37 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_env(t_envir *a, int i, char **cmd)
{
	if (cmd[1])
	{
		printf("env: %s: No such file or directory\n", cmd[1]);
		g_flags.exit_stat = 127;
		return ;
	}
	if (i)
		ft_env_ex(a);
	else
	{
		while (a)
		{
			if (a->value != NULL)
			{
				if (!ft_strcmp(a->variable, "PATH") && g_flags.path_fl == 1)
					printf("");
				else
					printf("%s=%s\n", a->variable, a->value);
			}
			a = a->next;
		}
	}
}
