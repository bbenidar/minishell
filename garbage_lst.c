/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 20:01:22 by bbenidar          #+#    #+#             */
/*   Updated: 2023/08/04 23:48:54 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_grbg	*ft_grbgnew(void *s)
{
	t_grbg	*node;

	node = malloc(sizeof(t_grbg));
	if (!node)
		exit (1);
	node->collector = s;
	node->next = 0;
	return (node);
}
t_grbg *ft_get_new_node(void)
{
	t_grbg	*node;

	node = malloc(sizeof(t_grbg));
	node->collector = NULL;
	node->next = NULL;
	return(node);
}
	

void	ft_grbgadd_front(t_grbg **lst, t_grbg *new)
{
	if (!lst || !new)
		return ;
	new -> next = *lst;
	*lst = new;
}



int	garbg_size(t_grbg *lst)
{
	t_grbg	*i;
	int		count;

	if (!lst)
		return (0);
	count = 0;
	i = lst;
	while (i)
	{
		count++;
		i = i->next;
	}
	return (count);
}

void	ft_grbgclear(t_grbg **lst)
{
	int			size;
	t_grbg		*tmp;

	if (!(*lst))
		return ;
	size = garbg_size(*lst);
	while (size--)
	{
		tmp = (*lst)->next;
		free((*lst)->collector);
		free(*lst);
		*lst = tmp;
	}
}

// void	ft_grbgadd_back(t_grbg **lst, t_grbg *new)
// {
// 	t_grbg	*check;

// 	if (!new)
// 		return ;
// 	if (!(*lst))
// 	{
// 		new->next = *lst;
// 		*lst = new;
// 		return ;
// 	}
// 	check = *lst;
// 	while (check->next)
// 		check = check->next;
// 	check->next = new;
// }
