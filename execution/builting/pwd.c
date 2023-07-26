/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakarkal <sakarkal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:23:57 by sakarkal          #+#    #+#             */
/*   Updated: 2023/07/26 15:23:58 by sakarkal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../minishell.h"

void				ft_pwd(void)
{
	char buffer[4096];

	getcwd(buffer, sizeof(buffer));
		// perror("minishell");
	printf("-> %s\n", buffer);
}
