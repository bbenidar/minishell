/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execut_help.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 21:31:21 by bbenidar          #+#    #+#             */
/*   Updated: 2023/08/11 21:34:29 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_lstlast_size(t_last *lst)
{
	int		c;
	t_last	*p;

	c = 0;
	p = lst;
	while (p)
	{
		p = p -> next;
		c++;
	}
	return (c);
}

char	*dell_quots(char *line)
{
	int		i;
	char	*str;
	int		j;

	j = 0;
	if (!line)
		return (NULL);
	i = ft_strlen_nospace(line);
	str = (char *)malloc(sizeof(char) * i + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (line[j])
	{
		if (line[j] != 34 && line[j] != 39)
		{
			str[i] = line[j];
			i++;
		}
		j++;
	}
	str[i] = '\0';
	free(line);
	return (str);
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
			if (!ft_strcmp(last->word[i], "\"\"" )
				|| !ft_strcmp(last->word[i], "\'\'" ))
				last->word[i] = ft_strdup(" ");
			else
				last->word[i] = dell_quots(last->word[i]);
			i++;
		}
		last = last->next;
	}
}

char	**ft_copy_tab(char **env)
{
	int		i;
	char	**ret;

	i = 0;
	while (env[i])
		i++;
	ret = malloc(sizeof(char *) * i + 1);
	i = 0;
	while (env[i])
	{
		ret[i] = ft_strdup(env[i]);
		i++;
	}
	ret[i] = 0;
	return (ret);
}
