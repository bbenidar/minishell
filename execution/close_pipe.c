/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakarkal <sakarkal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 09:33:23 by sakarkal          #+#    #+#             */
/*   Updated: 2023/08/10 09:33:26 by sakarkal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_pipe(int pipe_fds[2])
{
	close(pipe_fds[0]);
	close(pipe_fds[1]);
}

char	**ft_copy_tab(char **env)
{
	int		i;
	char	**ret;

	i = 0;
	while (env[i])
		i++;
	ret = malloc(sizeof(char *) * i + 1);
	i = 0;
	while (env[i])
	{
		ret[i] = ft_strdup(env[i]);
		i++;
	}
	ret[i] = 0;
	return (ret);
}
