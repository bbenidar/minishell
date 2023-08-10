/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_last_size.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakarkal <sakarkal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 09:33:18 by sakarkal          #+#    #+#             */
/*   Updated: 2023/08/10 09:33:20 by sakarkal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_lstlast_size(t_last *lst)
{
	int		c;
	t_last	*p;

	c = 0;
	p = lst;
	while (p)
	{
		p = p -> next;
		c++;
	}
	return (c);
}
