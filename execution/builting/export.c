/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 06:29:19 by sakarkal          #+#    #+#             */
/*   Updated: 2023/08/10 19:02:35 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	upd_va(t_envir *existing, char *value, int should_join)
{
	if (should_join)
		existing->value = ft_strjoin(existing->value, value);
	else
		existing->value = ft_strdup(value);
}

void	ft_pros_one(t_envir *existing, char *cmd, int j)
{
	char	*variable;
	int		shld_jn;

	while (existing)
	{
		shld_jn = 0;
		variable = ft_get_variable(cmd, &j);
		if (variable[ft_strlen(variable) - 1] == '+')
		{
			shld_jn = 1;
			variable[ft_strlen(variable) - 1] = '\0';
		}
		if (ft_strcmp(existing->variable, variable) == 0)
		{
			if (cmd[j] == '=')
			{
				j++;
				if (cmd[j])
					upd_va(existing, ft_get_value(cmd + j), shld_jn);
			}
			break ;
		}
		existing = existing->next;
	}
}

void	export_single_variable(t_envir *env, char *cmd, int i)
{
	int		j;
	t_envir	*tmp;
	t_envir	*existing;

	i = 0;
	j = 0;
	tmp = return_back_ptr(env);
	if (variable_exists(env, ft_get_variable(cmd, &j)))
	{
		existing = env;
		ft_pros_one(existing, cmd, j);
	}
	else
	{
		tmp = return_back_ptr(env);
		ft_pros_two(tmp, cmd, j, i);
	}
}

void	export_multiple_variables(t_envir *env, char **cmd)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	cmd++;
	while (cmd[i])
	{
		if (!ft_strcmp(cmd[i], "PATH"))
			g_flags.path_fl = 0;
		export_single_variable(env, cmd[i], i);
		i++;
	}
}

void	ft_export(t_envir *env, char **cmd)
{
	if (!cmd[1])
	{
		ft_env_ex(env);
		return ;
	}
	if (!check_expo(cmd))
		return (ft_putendl_fd("minishell : not a valid identifier", 2));
	export_multiple_variables(env, cmd);
}
