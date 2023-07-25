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
	if(str[1] && str[2])
		printf("exit\nminshell: exit: too many arguments\n");
	else
	{
		printf("exit\n");
		if(str[1])
			exit(ft_atoi(str[1]));
		else
			exit(0);
	}
}