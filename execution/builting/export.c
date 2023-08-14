/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 06:29:19 by sakarkal          #+#    #+#             */
/*   Updated: 2023/08/14 11:56:25 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	upd_va(t_envir *existing, char *value, int should_join)
{
	if (should_join)
	{
		if (!existing->value)
			existing->value = ft_strdup(value);
		else if (existing->value)
			existing->value = ft_strjoin(existing->value, value);
		free_add(existing);
	}
	else if (value)
	{
		free(existing->value);
		existing->value = ft_strdup(value);
		if (!existing->equal)
			existing->equal = ft_strdup("=");
		else
		{
			free(existing->equal);
			existing->equal = ft_strdup("=");
		}
	}
	free(value);
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
				if (cmd[++j])
					upd_va(existing, ft_get_value(cmd + j), shld_jn);
			free(variable);
			break ;
		}
		free(variable);
		existing = existing->next;
	}
}

void	export_single_variable(t_envir *env, char **cmd, int i)
{
	int		j;
	t_envir	*tmp;
	t_envir	*existing;

	j = 0;
	tmp = return_back_ptr(env);
	if (variable_exists(env, ft_get_variable(cmd[i], &j)))
	{
		existing = env;
		ft_pros_one(existing, cmd[i], j);
	}
	else
	{
		tmp = return_back_ptr(env);
		if (!tmp)
		{
			tmp = creat_env_list();
			ft_pros_two(tmp, cmd, j, i);
		}
		else
		{
			tmp->next = creat_env_list();
			ft_pros_two(tmp->next, cmd, j, i);
		}
	}
}

void	export_multiple_variables(t_envir *env, char **cmd)
{
	int		i;

	i = 0;
	cmd++;
	while (cmd[i])
	{
		if (!check_expo(cmd[i]))
		{
			i++;
			ft_putendl_fd("minishell : not a valid identifier", 2);
			if (!cmd[i])
			{
				g_flags.exit_stat = 1 * 256;
				return ;
			}
		}
		else
		{
			if (!ft_strcmp(cmd[i], "PATH"))
				g_flags.path_fl = 0;
			export_single_variable(env, cmd, i);
			i++;
		}
	}
}

void	ft_export(t_envir **env, char **cmd)
{
	if (!cmd[1])
		return (ft_env_ex(*env));
	export_multiple_variables(*env, cmd);
}
