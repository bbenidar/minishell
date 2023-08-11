/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 23:45:02 by bbenidar          #+#    #+#             */
/*   Updated: 2023/08/11 19:40:44 by bbenidar         ###   ########.fr       */
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

char	*ft_getfile_name(char **cammnd, t_envir *envr)
{
	char	*str;
	char	**paths;
	int		i;

	if (ft_strchr_sla(cammnd[0], '/') == 1)
		return (cammnd[0]);
	str = getfile_name_helper(envr);
	if (!str)
		return (NULL);
	paths = ft_split(str, ':');
	free(str);
	str = ft_strjoin(ft_strjoin
			(ft_strjoin(ft_strdup(""), paths[0]), "/"), cammnd[0]);
	i = 0;
	while (paths[++i])
	{
		if (!access(str, F_OK))
			return (str);
		free(str);
		str = ft_strjoin(ft_strjoin(ft_strjoin
					(ft_strdup(""), paths[i]), "/"), cammnd[0]);
	}
	return (NULL);
}

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

int	ft_check_for_ex(t_last *last, t_last *prv, t_envir **env, int size)
{
	if (last->word[0])
	{
		if (last->word[0] && !ft_strcmp(last->word[0], "exit"))
		{
			if (!last->next && !prv && size <= 1)
				ft_exit(last->word);
			return (0);
		}
		else if (last->word[0] && !ft_strcmp(last->word[0], "cd"))
		{
			if (size <= 1)
				ft_cd(last->word[1], *env);
			return (0);
		}
		else if (last->word[1] && !ft_strcmp(last->word[0], "export"))
		{
			if (size <= 1)
				ft_export(env, last->word);
			return (0);
		}
		else if (last->word[0] && !ft_strcmp(last->word[0], "unset"))
			if (size <= 1)
				return (ft_unset(env, last->word), 0);
	}
	return (1);
}
