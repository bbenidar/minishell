/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_variabl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 00:05:45 by bbenidar          #+#    #+#             */
/*   Updated: 2023/08/16 15:58:02 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**merg_and_split_multiple_time(char *line)
{
	char	**src;

	src = ft_split_opera(line, '\"');
	free(line);
	line = merge_str(src);
	free_tab(src);
	src = ft_split_opera(line, '\'');
	free(line);
	line = merge_str(src);
	free_tab(src);
	src = ft_split_opera(line, '/');
	free(line);
	line = merge_str(src);
	free_tab(src);
	src = ft_split_opera(line, '$');
	free(line);
	line = merge_str(src);
	free_tab(src);
	src = merg_and_split_multiple_time_1(line);
	line = merge_str(src);
	free_tab(src);
	src = merg_and_split_multiple_time_2(line);
	return (src);
}

void	process_variable_subs(char **src, t_envir *envr, int f, int i)
{
	while (src && src[++i])
	{
		if (src[i + 1] && (!ft_strcmp(src[i], "<<") || src[i][0] == '\''))
		{
			if (ft_strcmp(src[i], "\'"))
				g_flags.qts_flgs *= -1;
			while (src[i + 1] && (src[i + 1][0] == (' ' * -2)
				|| src[i + 1][0] == '\"'))
				i++;
			if (src[i + 1] && src[i + 1][0] == '$'
				&& !f && g_flags.qts_flgs == -1)
				src[i + 1][0] *= -1;
		}
		else if (!ft_strcmp(src[i], "$") && (src[i + 1]))
		{
			if ((src[i + 1][0] != ' ' * -2 && src[i + 1][0] != ' ' * -1
				&& src[i + 1][0] != '\"' && src[i + 1][0] != '\''))
				src[i + 1] = find_value(src[i + 1], envr);
			if (!ft_strcmp(src[i + 1], ""))
			{
				free(src[i]);
				src[i] = ft_strdup("");
			}
		}
	}
}

static void	process_variable_substitution_2(char **src, int i, int j)
{
	while (src && src[i])
	{
		if (src[i][0] == '$')
		{
			j = -1;
			if (!src[i + 1])
			{
				while (src[i][++j])
				{
					if (src[i][j] != '?')
						src[i][j] *= -1;
				}
			}
			else if (!ft_strcmp(src[i + 1], "\"") || !ft_strcmp(src[i + 1], "\'")
				|| src[i][1] == '$' || src[i + 1][0] == 32 * -2)
			{
				while (src[i][++j])
					src[i][j] *= -1;
			}
		}
		i++;
	}
}

static void	normalize_special_chars(char *line)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		if (line[i] == ' ' * -2)
			line[i] = ' ';
		else if (line[i] == '$' * -1)
			line[i] = '$';
		i++;
	}
}

char	*ft_add_variables(char *line, t_envir *envr, int f)
{
	int		i;
	int		j;
	int		len;
	char	**src;

	len = 0;
	j = 0;
	if (!f)
		ft_check_delim(line);
	convert_special_chars(line);
	i = 0;
	src = merg_and_split_multiple_time(line);
	process_variable_subs(src, envr, f, -1);
	process_variable_substitution_2(src, 0, 0);
	line = merge_tab(src);
	free_tab(src);
	src = ft_split(line, '$');
	free(line);
	line = merge_tab(src);
	normalize_special_chars(line);
	free_tab(src);
	ft_last_check(line);
	return (line);
}
