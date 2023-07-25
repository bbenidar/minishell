#include"../../minishell.h"

void				ft_pwd(void)
{
	char buffer[4096];

	getcwd(buffer, sizeof(buffer));
		// perror("minishell");
	printf("-> %s\n", buffer);
}

void	ft_exit(char **str)
{
	int i;
	
	i = 0;
	// if()
	printf("exit\n");
	exit(0);
}