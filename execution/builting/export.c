/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakarkal <sakarkal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 03:41:35 by sakarkal          #+#    #+#             */
/*   Updated: 2023/07/31 05:19:55 by sakarkal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_get_variable(char *str, int *i)
{
	char	*ret;
	int		j;

	j = *i;
	while (str[j] && str[j] != '=')
		j++;
	*i = j;
	ret = malloc(sizeof(char) * j + 1);
	j = 0;
	while (j < *i)
	{
		ret[j] = str[j];
		j++;
	}
	ret[j] = 0;
	return (ret);
}

char	*ft_get_value(char *str)
{
	return (ft_strdup(str));
}

int	variable_exists(t_envir *env, const char *variable)
{
	t_envir	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->variable && ft_strcmp(tmp->variable, (char *)variable) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	ft_export(t_envir *env, char **cmd)
{
	int		i;
	int		j;
	t_envir	*tmp;
	t_envir	*existing;

	i = 0;
	j = 0;
	tmp = return_back_ptr(env);
	if (!cmd[1])
	{
		ft_env_ex(env);
		return ;
	}
	cmd++;
	tmp->next = creat_env_list();
	tmp = tmp->next;
	while (cmd[i])
	{
		if (!ft_strcmp(cmd[i], "PATH"))
			flags.path_fl = 0;
		if (variable_exists(env, ft_get_variable(cmd[i], &j)))
		{
			existing = env;
			while (existing)
			{
				if (ft_strcmp(existing->variable, \
					ft_get_variable(cmd[i], &j)) == 0)
				{
					if (cmd[i][j] == '=')
					{
						j++;
						if (cmd[i][j])
						{
							free(existing->value);
							existing->value = ft_get_value(cmd[i] + j);
						}
					}
					break ;
				}
				existing = existing->next;
			}
		}
		else
		{
			tmp->value = ft_strdup("");
			j = 0;
			tmp->variable = ft_get_variable(cmd[i], &j);
			if (cmd[i][j] == '=')
			{
				tmp->equal = ft_strdup("=");
				j++;
				if (cmd[i][j])
				{
					tmp->value = ft_get_value(cmd[i] + j);
				}
			}
			else
			{
				tmp->value = NULL;
				tmp->equal = NULL;
			}
			if (cmd[i + 1])
			{
				tmp->next = creat_env_list();
				tmp = tmp->next;
			}
		}
		i++;
	}
}
