/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execut_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 23:55:22 by bbenidar          #+#    #+#             */
/*   Updated: 2023/08/10 23:55:47 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env_ex(t_envir *a)
{
	t_envir	*sorted_exp;

	sorted_exp = sort_env(a);
	while (sorted_exp)
	{
		if (sorted_exp->equal != NULL)
		{
			if (sorted_exp->value != NULL)
			{
				if (!ft_strcmp(sorted_exp->variable, "PATH")
					&& g_flags.path_fl == 1)
					printf("");
				else
					printf("declare -x %s=\"%s\"\n",
						sorted_exp->variable, sorted_exp->value);
			}
			else
				printf("declare -x %s=\"\"\n", sorted_exp->variable);
		}
		else
			printf("declare -x %s\n", sorted_exp->variable);
		sorted_exp = sorted_exp->next;
	}
}

void	close_pipe(int pipe_fds[2])
{
	close(pipe_fds[0]);
	close(pipe_fds[1]);
}

void	ret_toreal_v(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		return_space_to_real_value(str[i]);
		i++;
	}
}
