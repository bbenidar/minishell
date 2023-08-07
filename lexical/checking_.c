/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 20:38:58 by bbenidar          #+#    #+#             */
/*   Updated: 2023/08/07 21:15:28 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cheking_(t_stack *tmp)
{
	t_stack	*list;

	list = tmp;
	while (list && list->next)
	{
		if (list->key == RED_APP)
		{
			if (list->next->key != OPTION)
			{
				if (list->next->key == PIPE)
					printf("ERROR :syntax error near unexpected token `>>`\n");
				return (0);
			}
			list->next->key = FILE_APP;
		}
		else if (list->key == RED_OUT)
		{
			if (list->next->key != OPTION)
			{
				printf("ERROR :syntax error near unexpected token `<`\n");
				return (0);
			}
			list->next->key = FILE_OUT;
		}
		else if (list->key == RED_IN)
		{
			if (list->next->key != OPTION)
			{
				printf("ERROR :syntax error near unexpected token `>'\n");
				return (0);
			}
			list->next->key = FILE_IN;
		}
		else if (list->key == RED_HER)
		{
			if (list->next->key != OPTION)
			{
				printf("ERROR :syntax error near unexpected token `<<'\n");
				return (0);
			}
			list->next->key = LIMITER;
		}
		list = list->next;
	}
	return (1);
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
			while (str[i] && str[i] != ' ')
			{
				if (str[i] == '\"')
					g_flags.delim_flags++;
				if (str[i] == '\"' && str[i + 1] == '\"' && str[i + 2] == ' ')
				{
					str[i] *= -1;
					str[i + 1] *= -1;
				}
				if (str[i] == '\'' && str[i + 1] == '\'' && str[i + 2] == ' ')
				{
					str[i] *= -1;
					str[i + 1] *= -1;
				}
				if (str[i] == '$')
					str[i] *= -1;
				i++;
			}
		}
		i++;
	}
	g_flags.delim_flags /= 2;
}

int	check_any_redire(char *str, t_stack **wrd)
{
	int	i;

	i = 0;
	if (str[i] == '>')
	{
		if (str[i + 1] == '>')
		{
			printf("kksks\n");
			(*wrd)->next = ft_my_lstnew(">>", RED_APP);
			return (2);
		}
		else
		{
			(*wrd)->next = ft_my_lstnew(">", RED_OUT);
			return (1);
		}
	}
	if (str[i] == '<')
	{
		if (str[i + 1] == '<')
		{
			(*wrd)->next = ft_my_lstnew("<<", RED_HER);
			return (2);
		}
		else
		{
			(*wrd)->next = ft_my_lstnew("<", RED_IN);
			return (1);
		}
	}
	return (0);
}

