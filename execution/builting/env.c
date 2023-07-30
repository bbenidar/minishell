#include "../../minishell.h"

void	ft_env(t_envir *a)
{
	while (a)
	{
		if(a->value != NULL)
		{
			if (!ft_strcmp(a->variable, "PATH")  && flags.path_fl == 1)
                    printf("");
            else
				printf("%s=%s\n", a->variable, a->value);
		}
			
		a = a->next;
	}
}
