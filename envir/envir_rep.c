/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envir_rep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:40:17 by bbenidar          #+#    #+#             */
/*   Updated: 2023/08/12 21:05:30 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_variabl(char *str)
{
	int		i;
	char	*ret;

	i = 0;
	while (str[i] != '=')
		i++;
	ret = malloc(sizeof(char) * (i + 1));
	if (!ret)
		exit(1);
	i = -1;
	while (str[++i] != '=')
		ret[i] = str[i];
	ret[i] = '\0';
	return (ret);
}

char	*ft_value_of_shlvl(char *str)
{
	g_flags.shlvl = ft_atoi(str);
	free(str);
	++g_flags.shlvl;
	if (g_flags.shlvl == 1000)
		return (ft_strdup(""));
	else if (g_flags.shlvl < 0)
		return (ft_strdup("0"));
	else if (g_flags.shlvl > 1000)
		return (ft_strdup("1"));
	return (ft_itoa(g_flags.shlvl++));
}

char	*ft_value(char *str)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	while (str[j] && str[j] != '=')
		j++;
	if (!str[j])
		return (NULL);
	j++;
	ret = ft_strdup(str + j);
	return (ret);
}

t_envir	*create_env_list_from_env(char **env, int i)
{
	t_envir	*list;
	t_envir	*current;
	char	*str;

	list = creat_env_list();
	current = list;
	while (env[i])
	{
		current->variable = ft_variabl(env[i]);
		if (!ft_strcmp(current->variable, "SHLVL"))
		{
			str = ft_value(env[i]);
			current->value = ft_value_of_shlvl(str);
		}
		else
			current->value = ft_value(env[i]);
		if (current->value)
			current->equal = ft_value("=");
		if (env[++i])
		{
			current->next = creat_env_list();
			current = current->next;
		}
	}
	return (list);
}

t_envir	*replace_variables(char **env, int i)
{
	t_envir	*list;
	t_envir	*ret;

	if (env[0])
	{
		list = create_env_list_from_env(env, i);
		ret = list;
	}
	else
		ret = ft_no_env();
	return (ret);
}
