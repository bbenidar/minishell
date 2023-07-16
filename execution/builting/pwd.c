#include"../../minishell.h"

void				ft_pwd(void)
{
	char buffer[4096];

	if (getcwd(buffer, sizeof(buffer)) == NULL)
		perror("minishell");
	printf("-> %s\n", buffer);
}

void	ft_exit()
{
	printf("exit\n");
	exit(0);
}