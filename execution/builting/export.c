/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakarkal <sakarkal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 06:29:19 by sakarkal          #+#    #+#             */
/*   Updated: 2023/08/10 09:17:55 by sakarkal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_get_value(char *str)
{
	return (ft_strdup(str));
}

int	variable_exists(t_envir *env, char *variable)
{
	t_envir	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->variable && ft_strcmp(tmp->variable, variable) == 0)
		{
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	check_expo(char **str)
{
	int		i;
	int		j;
	char	*cmd;

	i = 0;
	j = 0;
	while (str[i])
	{
		j = 0;
		cmd = ft_get_variable(str[i], &j);
		j = 0;
		while (cmd[j])
		{
			if ((ft_isalpha(cmd[j]) || cmd[j] == '_') && j == 0)
				j++;
			else if ((ft_isalpha(cmd[j]) || ft_isdigit(cmd[j]) 
					|| cmd[j] == '_') && j != 0)
				j++;
			else
				return (0);
		}
		free(cmd);
		i++;
	}
	return (1);
}

void	ft_export(t_envir *env, char **cmd)
{
	int		i;
	int		j;
	t_envir	*tmp;
	t_envir	*existing;
	t_envir	*new_node;

	i = 0;
	j = 0;
	tmp = return_back_ptr(env);
	if (!cmd[1])
	{
		ft_env_ex(env);
		return ;
	}
	if (!check_expo(cmd))
		return (ft_putendl_fd("minishell : export : not a valid identifier",
				2));
	i = 0;
	j = 0;
	cmd++;
	if (!variable_exists(env, ft_get_variable(cmd[i], &j)))
	{
		tmp->next = creat_env_list();
		tmp = tmp->next;
	}
	while (cmd[i])
	{
		if (!ft_strcmp(cmd[i], "PATH"))
			g_flags.path_fl = 0;
		if (variable_exists(env, ft_get_variable(cmd[i], &j)))
		{
			existing = env;
			while (existing)
			{
				if (ft_strcmp(existing->variable, 
						ft_get_variable(cmd[i], &j)) == 0)
				{
					if (cmd[i][j] == '=')
					{
						j++;
						if (cmd[i][j])
						{
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
				new_node = creat_env_list();
				tmp->next = new_node;
				tmp = new_node;
			}
		}
		i++;
	}
}
