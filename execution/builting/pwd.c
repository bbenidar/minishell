/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:23:57 by sakarkal          #+#    #+#             */
/*   Updated: 2023/08/11 20:28:28 by bbenidar         ###   ########.fr       */
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

	if (!getcwd(buffer, sizeof(buffer)))
		perror("minishell");
	printf("%s\n", buffer);
}
