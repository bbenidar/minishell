/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messoufi <messoufi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:55:58 by messoufi          #+#    #+#             */
/*   Updated: 2023/05/24 11:47:48 by messoufi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	put_in_array(char **array, char *content)
{
	int		i;
	char	**arg;

	i = 0;
	arg = ft_split(content, '=');
	i = array_compare(array, arg, i);
	if (array[i] == NULL)
	{
		glv_mini.array = add_line_to_array(array, content);
		free_tab(arg);
		return ;
	}
	free(array[i]);
	content = ft_strdup(content);
	array[i] = content;
	free_tab(arg);
}

char	*ft_get_array(char **array, char *arg)
{
	int		i;
	char	*content;
	char	**spl;

	i = 0;
	content = NULL;
	while (array[i])
	{
		spl = ft_split(array[i], '=');
		if (spl != NULL && spl[0] != NULL && strcmp(spl[0], arg) == 0)
		{
			content = spl[1];
			break ;
		}
		free_tab(spl);
		i++;
	}
	return (content);
}
