/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messoufi <messoufi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:15:01 by messoufi          #+#    #+#             */
/*   Updated: 2023/05/24 11:45:58 by messoufi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit(t_mini *mini, char **command)
{
	mini->exit = 1;
	printf("exit ");
	if (command[1] != NULL)
	{
		printf("there is an argument after exit\n");
		if (command[2] != NULL)
		{
			mini->rtn = 1;
			printf("minishell: exit: there are too many arguments\n");
		}
		else if (!is_numeric(command[1]))
		{
			mini->rtn = 255;
			printf("minishell: exit: %s: numeric argument needed\n",
					command[1]);
		}
		else
		{
			mini->rtn = atoi(command[1]);
		}
	}
	else
	{
		printf("no argument\n");
		mini->rtn = 0;
	}
}
