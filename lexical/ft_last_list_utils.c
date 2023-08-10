/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_last_list_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 22:13:02 by bbenidar          #+#    #+#             */
/*   Updated: 2023/08/10 16:10:33 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_for_herdoc(t_stack	*tmp, t_envir *envr, t_last	*last)
{
	while (tmp)
	{
		if (tmp && (!ft_strcmp(tmp->word, "<<")
				&& tmp->key == RED_HER))
		{
			last->input = ft_herdoc(tmp, envr);
			if (last->input < 0)
			{
				if (last->input == -1)
					perror(tmp->word);
				return (0);
			}
			tmp->key = OPTION;
		}
		tmp = tmp->next;
	}
	return (1);
}

int	handle_file_output(t_stack *tmp, int key)
{
	int	fd_out;

	if (!ft_strcmp(tmp->word, "\"\"") || !ft_strcmp(tmp->word, "\'\'"))
	{
		free(tmp->word);
		tmp->word = ft_strdup("");
	}
	fd_out = open_fd_out(tmp->word, key);
	return (fd_out);
}

void	handle_file_input(t_last *last, t_stack *tmp)
{
	if (!ft_strcmp(tmp->word, "\"\"") || !ft_strcmp(tmp->word, "\'\'"))
	{
		free(tmp->word);
		tmp->word = ft_strdup("");
	}
	last->input = open(tmp->word, O_RDONLY, 0777);
	if (last->input < 0)
	{
		last->output = 1;
		last->input = 0;
		last->word = NULL;
		perror(tmp->word);
		while (tmp && tmp->key != PIPE)
			tmp = tmp->next;
		if (tmp && tmp->next != NULL)
			tmp = tmp->next;
	}
}

int	handle_herdoc(t_stack *tmp, t_envir *envr, t_last *last, int i)
{
	if (!i)
	{
		if (!ft_check_for_herdoc(tmp, envr, last))
			return (-1);
		return (1);
	}
	return (i);
}
