/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 13:21:07 by bbenidar          #+#    #+#             */
/*   Updated: 2023/08/16 15:57:26 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return ;
	else
	{
		ft_putstr_fd(s, fd);
		write(fd, "\n", 1);
	}
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*nstr;
	size_t	len;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (free((char *)s1), NULL);
	len = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	nstr = (char *)malloc(sizeof(char) * (len + 1));
	if (!nstr)
		return (0);
	while (s1[i])
	{
		nstr[i] = s1[i];
		i++;
	}
	while (s2[j])
		nstr[i++] = s2[j++];
	nstr[i] = '\0';
	free((char *)s1);
	return (nstr);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
