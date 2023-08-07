/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 18:20:07 by bbenidar          #+#    #+#             */
/*   Updated: 2023/08/06 23:35:54 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_stack	*ft_new_node(void)
{
	t_stack	*begin;

	begin = (t_stack *)malloc(sizeof(t_stack));
	if (!begin)
		return (NULL);
	begin->word = 0;
	begin->key = -1;
	begin->next = NULL;
	return (begin);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_strlen_no_null(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

char *ft_strdup(const char *s1)
{
    size_t i = 0;
    size_t len = ft_strlen(s1);
    char *p = (char *)malloc(sizeof(char) * (len + 1)); // Add +1 for the null-terminator
    if (!p)
        return (NULL);
    while (i < len) // Use < instead of <= to avoid copying the null-terminator
    {
        p[i] = s1[i];
        i++;
    }
    p[i] = '\0'; // Add the null-terminator at the end of the duplicated string
    return (p);
}

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}
