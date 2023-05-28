/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messoufi <messoufi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 11:15:05 by messoufi          #+#    #+#             */
/*   Updated: 2023/05/24 11:45:36 by messoufi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	put_pwd(char *arg, char *c)
{
	char	*string;

	string = ft_strjoin(arg, c);
	put_in_array(glv_mini.array, string);
	free(string);
}

int	ft_cd(char *arg)
{
	char	c[PATH_MAX];

	if (arg == NULL)
	{
		arg = ft_get_array(glv_mini.array, "HOME") + 5;
		if ((arg - 5) == NULL)
		{
			printf("cd: HOME not set\n");
			return (EXIT_FAILURE);
		}
	}
	getcwd(c, sizeof(c));
	if (chdir(arg) == -1)
	{
		if (arg[0] == '\0')
			return (EXIT_FAILURE);
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd(": Not a file or directory", 2);
		return (EXIT_FAILURE);
	}
	put_pwd("OLDPWD=", c);
	getcwd(c, sizeof(c));
	put_pwd("PWD=", c);
	return (EXIT_SUCCESS);
}
