#include "../../minishell.h"

void	ft_env(t_envir *a)
{
	while (a)
	{
		if(a->value != NULL)
			printf("%s=%s\n", a->variable, a->value);
		a = a->next;
	}
}
