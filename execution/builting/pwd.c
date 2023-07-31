/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 15:23:57 by sakarkal          #+#    #+#             */
/*   Updated: 2023/07/30 15:16:53 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../minishell.h"

void				ft_pwd(void)
{
	char buffer[4096];
	getcwd(buffer, sizeof(buffer));
		// perror("minishell");
	printf("%s\n", buffer);
}
