/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_creation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 12:13:43 by bbenidar          #+#    #+#             */
/*   Updated: 2023/08/07 18:10:23 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_stack	*ft_my_lstnew(char *content, int key)
{
	t_stack	*n;

	n = (t_stack *)malloc(sizeof(*n));
	if (!n)
		return (0);
	n->word = content;
	n->key = key;
	n->next = NULL;
	return (n);
}

t_last	*ft_new_last_list(void)
{
	t_last	*n;

	n = (t_last *)malloc(sizeof(*n));
	if (!n)
		return (0);
	n->word = NULL;
	n->input = 0;
	n->output = 1;
	n->next = NULL;
	return (n);
}
