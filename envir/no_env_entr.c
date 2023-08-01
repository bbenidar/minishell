/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_env_entr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 18:07:52 by bbenidar          #+#    #+#             */
/*   Updated: 2023/08/01 18:08:05 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_envir	*ft_no_env(void)
{
	char	buffer[4096];
	t_envir	*list;
	t_envir	*ret;

	getcwd(buffer, sizeof(buffer));
	// flags.shlvl = ft_get_shlvl();
	list = creat_env_list();
	ret = list;
	list->variable = ft_strdup("PWD");
	list->equal = ft_strdup("=");
	list->value = ft_strdup(buffer);
	list->next = creat_env_list();
	list = list->next;
	list->variable = ft_strdup("SHLVL");
	list->equal = ft_strdup("=");
	list->value = ft_itoa(g_flags.shlvl);
	list->next = creat_env_list();
	list = list->next;
	list->variable = ft_strdup("_");
	list->equal = ft_strdup("=");
	list->value = ft_strdup("/usr/bin/env");
	list->next = creat_env_list();
	list = list->next;
	list->variable = ft_strdup("PATH");
	list->equal = ft_strdup("=");
	list->value = ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
	g_flags.path_fl = 1;
	return(ret);
}