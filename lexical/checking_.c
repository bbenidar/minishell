/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakarkal <sakarkal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 20:38:58 by bbenidar          #+#    #+#             */
/*   Updated: 2023/08/12 17:52:48 by sakarkal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_and_update_redirection(t_stack *list)
{
	if (list->next->key != OPTION)
	{
		if (list->next->key == PIPE)
			printf("ERROR :syntax error near unexpeckkted token `>>`\n");
		return (0);
	}
	return (1);
}

int	update_redirection_key(t_stack *list)
{
	if (list->key == RED_APP)
	{
		if (check_and_update_redirection(list) == 0)
			return (0);
		list->next->key = FILE_APP;
	}
	else if (list->key == RED_OUT)
	{
		if (check_and_update_redirection(list) == 0)
			return (0);
		list->next->key = FILE_OUT;
	}
	else if (list->key == RED_IN)
	{
		if (check_and_update_redirection(list) == 0)
			return (0);
		list->next->key = FILE_IN;
	}
	else if (list->key == RED_HER)
	{
		if (check_and_update_redirection(list) == 0)
			return (0);
		list->next->key = LIMITER;
	}
	return (1);
}

int	cheking_(t_stack *tmp)
{
	t_stack	*list;

	list = tmp;
	while (list && list->next)
	{
		if (update_redirection_key(list) == 0)
			return (0);
		list = list->next;
	}
	return (1);
}

void	process_quoted_delimiters(char *str, int *i)
{
	while (str[*i] && str[*i] != ' ')
	{
		if (str[*i] == '\"')
		{
			if (str[*i] == '\"' && str[*i + 1] == '\"' && str[*i + 2] == ' ')
				g_flags.delim_flags++;
			g_flags.delim_flags++;
		}
		if (str[*i] == '\"' && str[*i + 1] == '\"' && str[*i + 2] == ' ')
		{
			str[*i] *= -1;
			str[*i + 1] *= -1;
		}
		if (str[*i] == '\'' && str[*i + 1] == '\'' && str[*i + 2] == ' ')
		{
			str[*i] *= -1;
			str[*i + 1] *= -1;
		}
		if (str[*i] == '$')
			str[*i] *= -1;
		(*i)++;
	}
}

void	ft_check_delim(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] == '<')
		{
			i += 2;
			while (str[i] == ' ')
				i++;
			process_quoted_delimiters(str, &i);
		}
		i++;
	}
	g_flags.delim_flags /= 2;
}
