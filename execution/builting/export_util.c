/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakarkal <sakarkal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 05:19:44 by sakarkal          #+#    #+#             */
/*   Updated: 2023/07/31 05:20:02 by sakarkal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_envir	*return_back_ptr(t_envir *env)
{
	while (env->next)
		env = env->next;
	return (env);
}

void	ft_swap_node(t_envir *list)
{
	char	*tmp_value;
	char	*tmp_variable;
	char	*tmp_equal;

	tmp_value = list->value;
	tmp_variable = list->variable;
	tmp_equal = list->equal;
	list->value = list->next->value;
	list->variable = list->next->variable;
	list->equal = list->next->equal;
	list->next->value = tmp_value;
	list->next->variable = tmp_variable;
	list->next->equal = tmp_equal;
}

int	ft_strcasecmp(const char *s1, const char *s2)
{
	unsigned char	c1;
	unsigned char	c2;

	while (*s1 && *s2)
	{
		c1 = (unsigned char)ft_tolower(*s1);
		c2 = (unsigned char)ft_tolower(*s2);
		if (c1 != c2)
			return (c1 - c2);
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

t_envir	*sort_env(t_envir *env)
{
	t_envir	*tmp;
	int		swapped;
	t_envir	*ptr1;

	tmp = NULL;
	swapped = 1;
	if (!env)
		return (NULL);
	while (swapped)
	{
		swapped = 0;
		ptr1 = env;
		while (ptr1->next != tmp)
		{
			if (ft_strcasecmp(ptr1->variable, ptr1->next->variable) > 0)
			{
				ft_swap_node(ptr1);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		tmp = ptr1;
	}
	return (env);
}

void	ft_env_ex(t_envir *a)
{
	t_envir	*sorted_exp;

	sorted_exp = sort_env(a);
	while (a)
	{
		if (a->equal != NULL)
		{
			if (a->value != NULL)
			{
				if (!ft_strcmp(a->variable, "PATH") && flags.path_fl == 1)
					printf("");
				else
					printf("declare -x %s=\"%s\"\n", a->variable, a->value);
			}
			else
			{
				printf("declare -x %s=\"\"\n", a->variable);
			}
		}
		else
			printf("declare -x %s\n", a->variable);
		a = a->next;
	}
}
