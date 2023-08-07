/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_option.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 20:42:53 by bbenidar          #+#    #+#             */
/*   Updated: 2023/08/07 20:54:45 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_remove_gv(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 32 * -1)
			str[i] = 32;
		i++;
	}
}

void	ft_option(t_stack *list, t_last *str)
{
	t_stack	*tmp;
	char	*src;
	int		j;

	src = ft_strdup("");
	j = 0;
	tmp = list;
	while (tmp && tmp->key != PIPE)
	{
		if (tmp->key == COMMAND || tmp->key == OPTION)
		{
			src = ft_strjoin(src, tmp->word);
			src = ft_strjoin(src, "&");
		}
		tmp = tmp->next;
		j++;
	}
	ft_remove_gv(src);
	str->word = ft_split(src, '&');
	free(src);
}

int	option_len(t_stack *list)
{
	int	i;

	i = 0;
	while (list && (list->key != 11))
	{
		if (list->key == 2 || list->key == 1)
			i++;
		list = list->next;
	}
	return (i);
}

void	return_space_to_real_value(char *word)
{
	while (*word)
	{
		if (*word == 32 * -1 || *word == 60 * -1
			|| *word == '\'' * -1 || *word == '\"' * -1)
			*word *= -1;
		word++;
	}
}
