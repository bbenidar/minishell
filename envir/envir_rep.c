/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envir_rep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:40:17 by bbenidar          #+#    #+#             */
/*   Updated: 2023/08/05 00:21:18 by bbenidar         ###   ########.fr       */
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
	if(g_flags.grbg)
	{
		g_flags.grbg->next = ft_get_new_node();
		g_flags.grbg = g_flags.grbg->next;
	}
	else
	{
		g_flags.grbg = ft_get_new_node();
		g_flags.grbg_head = g_flags.grbg;
	}
	g_flags.grbg->collector = ret;
	i = -1;
	while (str[++i] != '=')
		ret[i] = str[i];
	ret[i] = '\0';
	return (ret);
}

char	*ft_value_of_shlvl(char *str)
{
	g_flags.shlvl = ft_atoi(str);
	++g_flags.shlvl;
	return (ft_itoa(g_flags.shlvl++));
}

char	*ft_value(char *str)
{
	int		i;
	char	*ret;

	i = 0;
	while (*str && *str != '=')
		str++;
	str++;
	while (str[i])
		i++;
	ret = malloc(sizeof(char) * (i + 1));
	if(g_flags.grbg)
	{
		g_flags.grbg->next = ft_get_new_node();
		g_flags.grbg = g_flags.grbg->next;
	}
	else
	{
		g_flags.grbg = ft_get_new_node();
		g_flags.grbg_head = g_flags.grbg;
	}
	g_flags.grbg->collector = ret;
	i = -1;
	while (str[++i])
		ret[i] = str[i];
	ret[i] = '\0';
	return (ret);
}

t_envir	*replace_variables(char **env, int i)
{
	t_envir	*list;
	t_envir	*ret;

	if (env[0])
	{
		list = creat_env_list();
		ret = list;
		while (env[i])
		{
			list->variable = ft_variabl(env[i]);
			if (!ft_strcmp(list->variable, "SHLVL"))
				list->value = ft_value_of_shlvl(ft_value(env[i]));
			else
				list->value = ft_value(env[i]);
			list->equal = ft_value("=");
			if (env[++i])
			{
				list->next = creat_env_list();
				list = list->next;
			}
		}
	}
	else
		ret = ft_no_env();
	return (ret);
}
