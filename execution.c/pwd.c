/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messoufi <messoufi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:16:16 by messoufi          #+#    #+#             */
/*   Updated: 2023/05/24 11:46:26 by messoufi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(void)
{
	char	c[PATH_MAX];

	if (getcwd(c, PATH_MAX))
	{
		ft_putendl_fd(c, 1);
		return(EXIT_SUCCESS);
	}
	else
		return(EXIT_FAILURE);
}
