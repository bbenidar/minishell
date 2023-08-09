/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_variabl_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 01:18:19 by bbenidar          #+#    #+#             */
/*   Updated: 2023/08/09 01:20:37 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*merge_str(char **str)
{
	int		i;
	char	*line;

	i = 0;
	if (!str)
		return (NULL);
	line = ft_strdup("");
	while (str[i])
	{
		line = ft_strjoin(line, str[i]);
		line = ft_strjoin(line, " ");
		i++;
	}
	return (line);
}

char	*find_value(char *str, t_envir *env)
{
	char	*ret;

	ret = ft_strdup("");
	if (str[0] == '?')
		ret = ft_strdup(ft_itoa(g_flags.exit_stat / 256));
	while (env)
	{
		if (!ft_strcmp(env->variable, str))
		{
			ret = ft_strjoin(ret, env->value);
			break ;
		}
		env = env->next;
	}
	free(str);
	return (ret);
}

void	convert_special_chars(char *line)
{
	while (*line)
	{
		if (*line == ' ')
			*line *= -2;
		line++;
	}
}

char	**merg_and_split_multiple_time_2(char *line)
{
	char	**src;

	src = ft_split_opera(line, '?');
	free(line);
	line = merge_str(src);
	free_tab(src);
	src = ft_split_opera(line, ' ' * -2);
	free(line);
	line = merge_str(src);
	free_tab(src);
	src = ft_split_opera(line, ' ' * -1);
	free(line);
	line = merge_str(src);
	free_tab(src);
	src = ft_split_opera(line, '<');
	free(line);
	line = merge_str(src);
	free_tab(src);
	src = ft_split(line, ' ');
	free(line);
	return (src);
}