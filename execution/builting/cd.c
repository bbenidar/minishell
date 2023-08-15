/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakarkal <sakarkal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 06:23:23 by sakarkal          #+#    #+#             */
/*   Updated: 2023/08/15 23:48:56 by sakarkal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_logine(t_envir *env)
{
	while (env)
	{
		if (!ft_strcmp(env->variable, "HOME"))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*get_path(t_envir *env)
{
	while (env)
	{
		if (!ft_strcmp(env->variable, "OLDPWD"))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	ft_cd(char *arg, t_envir *env)
{
	char	*login;
	char	*to_free;
	char	buffer[4096];

	login = get_logine(env);
	to_free = getcwd(buffer, sizeof(buffer));
	if (!arg)
	{
		if (login)
			chdir(login);
		else
		{
			g_flags.exit_stat = 1;
			printf("minishell: cd: HOME not set\n");
		}
		return ;
	}
	else
	{
		if (chdir(arg) == -1)
		{
			perror("minishell ");
			g_flags.exit_stat = 1 * 256;
		}
	}
}
