/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_creation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 12:13:43 by bbenidar          #+#    #+#             */
/*   Updated: 2023/08/04 23:40:03 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_stack *ft_my_lstnew(char *content, int key)
{
	t_stack *n;

	n = (t_stack *)malloc(sizeof(*n));
	if (!n)
		return (0);
	if(g_flags.grbg)
	{
		g_flags.grbg->next = ft_get_new_node();
		g_flags.grbg = g_flags.grbg->next;
	}
	else
	{
		g_flags.grbg = ft_get_new_node();
		g_flags.grbg_head = g_flags.grbg;
	}
	g_flags.grbg->collector = n;
	n->word = content;
	n->key = key;
	n->next = NULL;
	return (n);
}

t_last *ft_new_last_list()
{
	t_last *n;

	n = (t_last *)malloc(sizeof(*n));
	if (!n)
		return (0);
	if(g_flags.grbg)
	{
		g_flags.grbg->next = ft_get_new_node();
		g_flags.grbg = g_flags.grbg->next;
	}
	else
	{
		g_flags.grbg = ft_get_new_node();
		g_flags.grbg_head = g_flags.grbg;
	}
	g_flags.grbg->collector = n;
	n->word = NULL;
	n->input = 0;
	n->output = 1;
	n->next = NULL;
	return (n);
}