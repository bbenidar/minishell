/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execut.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakarkal <sakarkal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:24:13 by sakarkal          #+#    #+#             */
/*   Updated: 2023/08/10 09:36:41 by sakarkal         ###   ########.fr       */
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

char	*ft_getfile_name(char **cammnd, t_envir *envr)
{
	char	*str;
	char	**paths;
	int		i;

	str = NULL;
	i = 1;
	if (ft_strchr_sla(cammnd[0], '/') == 1)
	{
		return (cammnd[0]);
	}
	while (envr)
	{
		if (!ft_strcmp(envr->variable, "PATH"))
		{
			str = ft_strdup(envr->value);
			break ;
		}
		envr = envr->next;
	}
	paths = ft_split(str, ':');
	free(str);
	str = ft_strjoin(ft_strdup(""), paths[0]);
	str = ft_strjoin(str, "/");
	str = ft_strjoin(str, cammnd[0]);
	while (paths[i])
	{
		if (!access(str, F_OK))
		{
			return (str);
		}
		free(str);
		str = ft_strjoin(ft_strdup(""), paths[i]);
		str = ft_strjoin(str, "/");
		str = ft_strjoin(str, cammnd[0]);
		i++;
	}
	return (NULL);
}

void	ft_env_ex(t_envir *a)
{
	t_envir	*sorted_exp;

	sorted_exp = sort_env(a);
	while (sorted_exp)
	{
		if (sorted_exp->equal != NULL)
		{
			if (sorted_exp->value != NULL)
			{
				if (!ft_strcmp(sorted_exp->variable, "PATH")
					&& g_flags.path_fl == 1)
					printf("");
				else
					printf("declare -x %s=\"%s\"\n", sorted_exp->variable,
						sorted_exp->value);
			}
			else
				printf("declare -x %s=\"\"\n", sorted_exp->variable);
		}
		else
			printf("declare -x %s\n", sorted_exp->variable);
		sorted_exp = sorted_exp->next;
	}
}

void	ret_toreal_v(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		return_space_to_real_value(str[i]);
		i++;
	}
}

void	ft_rem_quo(t_last *last)
{
	int	i;

	i = 0;
	while (last)
	{
		i = 0;
		while (last->word[i])
		{
			if (!ft_strcmp(last->word[i], "\"\"") 
				|| !ft_strcmp(last->word[i], "\'\'"))
			{
				free(last->word[i]);
				last->word[i] = ft_strdup(" ");
			}
			i++; 
		}
		last = last->next;
	}
}
