/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakarkal <sakarkal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 09:38:07 by sakarkal          #+#    #+#             */
/*   Updated: 2023/08/10 10:11:13 by sakarkal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	built(t_last *last, t_last *prv, t_envir *env)
{
	int	i;

	if (last->word[0] && !ft_strcmp(last->word[0], "exit"))
	{
		if (!last->next && !prv)
			ft_exit(last->word);
		return ;
	}
	else if (last->word[0] && !ft_strcmp(last->word[0], "cd"))
	{
		ft_cd(last->word[1], env);
		return ;
	}
	else if (last->word[1] && !ft_strcmp(last->word[0], "export"))
	{
		ft_export(env, last->word);
		return ;
	}
	else if (last->word[0] && !ft_strcmp(last->word[0], "unset"))
	{
		i = 0;
		while (last->word[++i])
			ft_unset(&env, last->word[i]);
		return ;
	}
}

int	ft_check_for_ex(t_last *last, t_last *prv, t_envir *env, int size)
{
	if (last->word[0] && size <= 1)
	{
		built(last, prv, env);
	}
	return (1);
}
