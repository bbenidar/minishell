/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 09:08:17 by sakarkal          #+#    #+#             */
/*   Updated: 2023/08/13 13:30:09 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_free_node(t_envir *tmp)
{
	if (tmp->variable)
		free(tmp->variable);
	if (tmp->value)
		free(tmp->value);
	if (tmp->equal)
		free(tmp->equal);
	free(tmp);
}

t_envir	*rem_from_list(t_envir *env, char *cmd)
{
	t_envir	*tmp;
	t_envir	*ret;

	if (!ft_strcmp(env->variable, cmd))
	{
		ret = env->next;
		ft_free_node(env);
		return (ret);
	}
	ret = env;
	while (env && env->next)
	{
		if (env->next->variable && !ft_strcmp(env->next->variable, cmd))
		{
			tmp = env->next;
			ft_free_node(tmp);
			env->next = env->next->next;
			return (ret);
		}
		env = env->next;
	}
	return (ret);
}

int	ft_lstsize(t_envir *lst)
{
	int		c;
	t_envir	*p;

	c = 0;
	p = lst;
	while (p)
	{
		p = p -> next;
		c++;
	}
	return (c);
}

char	**ft_merge_envr(t_envir *env)
{
	char	**str;
	int		len;
	int		i;

	i = 0;
	len = ft_lstsize(env);
	str = NULL;
	str = malloc(sizeof(char *) * len + 1);
	if (!str)
		return (NULL);
	while (env)
	{
		str[i] = ft_strdup("");
		str[i] = ft_strjoin(str[i], env->variable);
		if (env->value)
		{
			str[i] = ft_strjoin(str[i], "=");
			str[i] = ft_strjoin(str[i], env->value);
		}
		env = env->next;
		i++;
	}
	str[i] = NULL;
	return (str);
}

void	ft_unset(t_envir **env, char **cmd)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		if (!check_expo(cmd[i]))
		{
			i++;
			ft_putendl_fd("minishell : not a valid identifier", 2);
			if (!cmd[i])
			{
				g_flags.exit_stat = 1;
				return ;
			}
		}
		else
		{
			*env = rem_from_list(*env, cmd[i]);
			i++;
		}
	}
}
