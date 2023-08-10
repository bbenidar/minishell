/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 11:39:12 by bbenidar          #+#    #+#             */
/*   Updated: 2023/08/10 17:24:40 by bbenidar         ###   ########.fr       */
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

void	lexical_function(char *line, char **env, t_envir **envr)
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
	if (last->word)
		ft_execution(last, env, envr);
	else
	{
		printf("minishell: :command not found\n");
		g_flags.exit_stat = 127 * 256;
	}
	cleanup_and_exit(&head, &last);
}
