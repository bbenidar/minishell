/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_built.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakarkal <sakarkal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 09:35:54 by sakarkal          #+#    #+#             */
/*   Updated: 2023/08/10 09:35:59 by sakarkal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_for_builting(t_last *last, t_envir *env)
{
	if (last->word[0])
	{
		if (!ft_strcmp(last->word[0], "echo"))
		{
			ft_echo(last, last->word);
			return (1);
		}
		else if (!ft_strcmp(last->word[0], "env"))
		{
			ft_env(env, 0);
			return (1);
		}
		else if (!last->word[1] && !ft_strcmp(last->word[0], "export"))
		{
			ft_env(env, 1);
			return (1);
		}
		else if (!ft_strcmp(last->word[0], "pwd"))
		{
			ft_pwd();
			return (1);
		}
	}
	return (0);
}
