/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakarkal <sakarkal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:23:57 by sakarkal          #+#    #+#             */
/*   Updated: 2023/08/15 23:50:56 by sakarkal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_add(t_envir *existing)
{
	if (!existing->equal)
		existing->equal = ft_strdup("=");
	else
	{
		free(existing->equal);
		existing->equal = ft_strdup("=");
	}
}

void	ft_pwd(void)
{
	char	buffer[4096];

	getcwd(buffer, sizeof(buffer));
	printf("%s\n", buffer);
}
