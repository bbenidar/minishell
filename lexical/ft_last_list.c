/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_last_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 06:10:52 by bbenidar          #+#    #+#             */
/*   Updated: 2023/08/13 15:27:35 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_options(t_stack *tmp, t_last *last, int i)
{
	if (tmp->word && tmp && i == 1 && ft_strcmp(tmp->word, "<<"))
	{
		ft_option(tmp, last);
		i = 0;
	}
	return (i);
}

int	handle_file_in(t_stack **tmp, t_last *last)
{
	if ((*tmp)->key == FILE_IN)
	{
		handle_file_input(last, tmp);
		if (last->input < 0)
		{
			last->output = 1;
			while (*tmp && (*tmp)->key != PIPE)
				*tmp = (*tmp)->next;
			if (*tmp && (*tmp)->next != NULL)
				*tmp = (*tmp)->next;
			return (0);
		}
	}
	return (1);
}

int	handle_file_ou(t_stack *tmp, t_last *last)
{
	if (tmp->key == FILE_OUT || tmp->key == FILE_APP)
	{
		if (last->output != 1)
			close(last->output);
		last->output = handle_file_output(tmp, tmp->key);
		if (last->output < 0)
		{
			last->word[0] = ft_strdup("");
			return (1);
		}
	}
	if (last->output < 0)
		return (1);
	return (1);
}

t_stack	*prossecc_2(t_stack *tmp, t_last *last, t_envir *envr, int *flag)
{
	int	i;

	i = 0;
	while (tmp && tmp->key != PIPE)
	{
		i = handle_herdoc(tmp, envr, last, i);
		if (i < 0 || g_flags.herdo_c == 1)
			return (NULL);
		*flag = handle_options(tmp, last, *flag);
		if (!handle_file_in(&tmp, last))
			return (tmp);
		else if (!handle_file_ou(tmp, last))
			return (NULL);
		tmp = tmp->next;
	}
	return (tmp);
}

t_last	*ft_last_list_get_ready(t_stack *head, t_envir *envr)
{
	t_last	*last;
	t_last	*ret;
	t_stack	*tmp;
	int		flag;

	tmp = head;
	last = ft_new_last_list();
	ret = last;
	while (tmp)
	{
		flag = 1;
		tmp = prossecc_2(tmp, last, envr, &flag);
		if (!tmp)
			break ;
		if (tmp && tmp->key == PIPE)
		{
			tmp = tmp->next;
			last->next = ft_new_last_list();
			last = last->next;
		}
	}
	return (ret);
}
