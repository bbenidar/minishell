/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 13:26:45 by bbenidar          #+#    #+#             */
/*   Updated: 2023/08/13 15:52:22 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_skip_qoutes(char *str)
{
	int		i;
	char	c;

	c = *str;
	if (c != 34 && c != 39)
		return (0);
	i = 1;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

static int	check_pipe(char *str)
{
	while (*str)
	{
		if ((*str == 124 && *(str + 1) != 124))
		{
			str++;
			while (*str == 32 || *str == '\t')
				str++;
			if (!*str || *str == 124 || *str == 38)
				return (1);
		}
		str += ft_skip_qoutes(str);
		if (*str)
			str++;
	}
	return (0);
}

static int	check_redir(char *str)
{
	while (*str)
	{
		if ((*str == 60 && *(str + 1) != 60)
			|| (*str == 62 && *(str + 1) != 62))
		{
			str++;
			while (*str == 32 || *str == '\t')
				str++;
			if (!*str || *str == 60 || *str == 62)
				return (1);
		}
		str += ft_skip_qoutes(str);
		if (((*str == 60 && *(str + 1) == 60)
				|| (*str == 62 && *(str + 1) == 62)))
		{
			str += 2;
			while ((*str == ' ' || *str == '\t'))
				str++;
			if (!*str || check_character(*str, "<>|"))
				return (1);
		}
		if (*str)
			str++;
	}
	return (0);
}

int	check_logical(char *str)
{
	while (*str)
	{
		if (*str == 38 || *str == 124)
		{
			str++;
			if (*str == 38)
				return (1);
			while (*str == 32)
				str++;
			if (check_character(*str, "&|"))
				return (1);
		}
		if (*str)
			str++;
	}
	return (0);
}

int	ft_first_check(char *str)
{
	if (str)
	{
		while (str && *str == ' ')
			str++;
		if (check_space(str))
			return (1);
		if (ft_check_quotes(str))
			printf("ERROR :Unclosed quotes\n");
		else if (*str == 124 || *str == 38 || check_pipe(str))
			printf("minishell: syntax error near unexpected token `| or &`\n");
		else if (check_redir(str))
			printf("minishell: syntax error near unexpected token `<'\n");
		else
			return (0);
	}
	return (1);
}
