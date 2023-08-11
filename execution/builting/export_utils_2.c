/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 18:56:12 by bbenidar          #+#    #+#             */
/*   Updated: 2023/08/11 20:28:16 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_get_value(char *str)
{
	return (ft_strdup(str));
}

int	variable_exists(t_envir *tmp, char *variable)
{
	char	*var_tmp;

	var_tmp = ft_strdup(variable);
	if (var_tmp[ft_strlen(var_tmp) - 1] == '+')
		var_tmp[ft_strlen(var_tmp) - 1] = '\0';
	while (tmp)
	{
		if (tmp->variable && ft_strcmp(tmp->variable, var_tmp) == 0)
		{
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	ft_is_valid(char c, int j)
{
	if ((ft_isalpha(c) || c == '_' ) && j == 0)
		return (1);
	else if ((ft_isalpha(c) || ft_isdigit(c) 
			|| c == '_') && j != 0)
		return (1);
	else
		return (0);
}

int	check_expo(char *str)
{
	int		j;
	char	*cmd;

	j = 0;
	cmd = ft_get_variable(str, &j);
	if (cmd[ft_strlen(cmd) - 1] == '+')
		cmd[ft_strlen(cmd) - 1] = '\0';
	j = 0;
	while (cmd[j])
	{
		if (!ft_is_valid(cmd[j], j))
			return (0);
		else
			j++;
	}
	free(cmd);
	return (1);
}

void	ft_pros_two(t_envir *tmp, char **cmd, int j, int i)
{
	tmp->value = ft_strdup("");
	j = 0;
	tmp->variable = ft_get_variable(cmd[i], &j);
	if (tmp->variable[ft_strlen(tmp->variable) - 1] == '+')
		tmp->variable[ft_strlen(tmp->variable) - 1] = '\0';
	if (cmd[i][j] == '=')
	{
		tmp->equal = ft_strdup("=");
		if (cmd[++j])
			tmp->value = ft_get_value(cmd[i] + j);
	}
	else
	{
		tmp->value = NULL;
		tmp->equal = NULL;
	}
}
