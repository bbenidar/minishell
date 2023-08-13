/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 23:45:02 by bbenidar          #+#    #+#             */
/*   Updated: 2023/08/13 13:36:24 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strchr_sla(char *s, int c)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] == (unsigned char)c)
			return (1);
	return (0);
}

char	*getfile_name_helper(t_envir *envr)
{
	char	*str;

	str = NULL;
	while (envr)
	{
		if (!ft_strcmp(envr->variable, "PATH"))
		{
			str = ft_strdup(envr->value);
			break ;
		}
		envr = envr->next;
	}
	if (!str)
		return (NULL);
	return (str);
}

int	ft_builting_2(t_last *last, t_envir *env)
{
	if (g_flags.size)
	{
		if (last->word[0] && !ft_strcmp(last->word[0], "exit"))
		{
			if (!last->next)
				ft_exit(last->word);
			return (1);
		}
		else if (last->word[0] && !ft_strcmp(last->word[0], "cd"))
			return (ft_cd(last->word[1], env), 1);
		else if (last->word[1] && !ft_strcmp(last->word[0], "export"))
		{
			ft_export(&env, last->word);
			return (1);
		}
		else if (last->word[0] && !ft_strcmp(last->word[0], "unset"))
			return (ft_unset(&env, last->word), 1);
	}
	return (0);
}

int	ft_check_for_builting(t_last *last, t_envir *env)
{
	if (last->word && last->word[0])
	{
		if (ft_builting_2(last, env))
			return (1);
		else if (!ft_strcmp(last->word[0], "echo"))
			return (ft_echo(last, last->word), 1);
		else if (!ft_strcmp(last->word[0], "env"))
		{
			ft_env(env, 0, last->word);
			return (1);
		}
		else if (!last->word[1] && !ft_strcmp(last->word[0], "export"))
		{
			ft_env(env, 1, last->word);
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

int	ft_check_for_ex(t_last *last, t_last *prv, t_envir **env)
{
	if (last->word && last->word[0])
	{
		if (last->word[0] && !ft_strcmp(last->word[0], "exit"))
		{
			if (!last->next && !prv)
				ft_exit(last->word);
			return (0);
		}
		else if (last->word[0] && !ft_strcmp(last->word[0], "cd"))
		{
			ft_cd(last->word[1], *env);
			return (0);
		}
		else if (last->word[1] && !ft_strcmp(last->word[0], "export"))
		{
			ft_export(env, last->word);
			return (0);
		}
		else if (last->word[0] && !ft_strcmp(last->word[0], "unset"))
			return (ft_unset(env, last->word), 0);
	}
	return (1);
}
