/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakarkal <sakarkal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 11:39:12 by bbenidar          #+#    #+#             */
/*   Updated: 2023/08/12 17:48:21 by sakarkal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cleanup_and_exit(t_stack **head, t_last **last)
{
	ft_free_stack(head);
	ft_free_last(last);
}

t_stack	*prepare_lexical_analysis(char *line)
{
	char	*str;
	t_stack	*head;

	str = split_for_lexical(line);
	head = split_in_list(str);
	free(str);
	return (head);
}

void	lexical_function(char *line, t_envir **envr)
{
	t_stack	*head;
	t_last	*last;

	head = prepare_lexical_analysis(line);
	if (!cheking_(head))
	{
		g_flags.exit_stat = 66048;
		return ;
	}
	last = ft_last_list_get_ready(head, *envr);
	if (!last)
	{
		cleanup_and_exit(&head, &last);
		return ;
	}
	if (last->word && g_flags.herdo_c != 1)
		ft_execution(last, envr);
	else if (!last->word && g_flags.herdo_c != 1)
		g_flags.exit_stat = 1 * 256;
	cleanup_and_exit(&head, &last);
}
