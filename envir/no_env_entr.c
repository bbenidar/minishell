/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_env_entr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 18:07:52 by bbenidar          #+#    #+#             */
/*   Updated: 2023/08/09 14:46:13 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_no_env_2(t_envir *list)
{
	list->variable = ft_strdup("PATH");
	list->equal = ft_strdup("=");
	list->value = ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
}

t_envir	*ft_no_env(void)
{
	char	buffer[4096];
	t_envir	*list;
	t_envir	*ret;

	getcwd(buffer, sizeof(buffer));
	list = creat_env_list();
	ret = list;
	list->variable = ft_strdup("PWD");
	list->equal = ft_strdup("=");
	list->value = ft_strdup(buffer);
	list->next = creat_env_list();
	list = list->next;
	list->variable = ft_strdup("SHLVL");
	list->equal = ft_strdup("=");
	list->value = ft_itoa(2);
	list->next = creat_env_list();
	list = list->next;
	list->variable = ft_strdup("_");
	list->equal = ft_strdup("=");
	list->value = ft_strdup("/usr/bin/env");
	list->next = creat_env_list();
	list = list->next;
	ft_no_env_2(list);
	g_flags.path_fl = 1;
	return (ret);
}
