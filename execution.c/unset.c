/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messoufi <messoufi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:15:43 by messoufi          #+#    #+#             */
/*   Updated: 2023/05/24 11:46:34 by messoufi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**remove_line_from_array(char **array, char *line)
{
	int		i;
	int		j;
	char	**new_array;

	i = 0;
	j = 0;
	while (array[i])
		i++;
	new_array = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (array[i])
	{
		if (ft_strcmp(array[i], line) == 0)
			i++;
		if (array[i])
		{
			new_array[j++] = ft_strdup(array[i]);
			i++;
		}
	}
	new_array[j] = NULL;
	free_tab(array);
	return (new_array);
}

int	check_arg_unset(char *arg)
{
	int	i;

	i = 0;
	if (ft_isalpha(arg[i]) == 0 && arg[i] != '_')
	{
		printf("unset: '%s': not a valid identifier\n", arg);
		return (1);
	}
	i++;
	while (arg[i])
	{
		if ((ft_isalnum(arg[i]) == 0 && arg[i] != '_') || arg[i] == '=')
		{
			printf("unset: '%s': not a valid identifier\n", arg);
			return (1);
		}
		i++;
	}
	return (0);
}

char	**remove_unset(char **array, char *arg)
{
	char	*line;

	line = NULL;
	line = ft_get_array(array, arg);
	if (line != NULL)
		array = remove_line_from_array(array, line);
	return (array);
}

int	ft_unset(char **arg)
{
	int i;
	char **strings;
	int ret;

	ret = 0;
	i = 0;
	while (arg[i])
	{
		if (check_arg_unset(arg[i]) != 0)
		{
			i++;
			ret = 1;
			continue ;
		}
		strings = ft_split(arg[i], '=');
		glv_mini.array = remove_unset(glv_mini.array, strings[0]);
		glv_mini.array_export = remove_unset(glv_mini.array_export, strings[0]);
		free_tab(strings);
		i++;
	}
	return (ret);
}
