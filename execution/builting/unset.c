
#include"../../minishell.h"

t_envir *rem_from_list(t_envir *env,char *cmd)
{
	t_envir *tmp;
	t_envir *ret;
	ret = env;
	tmp = env->next;
	
	if(!ft_strcmp(env->variable, cmd))
		return(free(env), tmp);
	tmp = env;
	env = env->next;

	while(env->next)
	{
		if(!ft_strcmp(env->variable, cmd))
		{
			tmp->next = env->next;
		}
		tmp = env;
		env = env->next;
	}
	return (ret);
}

int	ft_lstsize(t_envir *lst)
{
	int		c;
	t_envir	*p;

	c = 0;
	p = lst;
	while (p)
	{
		p = p -> next;
		c++;
	}
	return (c);
}

char **ft_merge_envr(t_envir *env)
{
	char **str = NULL;
	int len;
	int i;

	i = 0;
	len = ft_lstsize(env);
	str = malloc(sizeof(char *) * len + 1);
	while(env)
	{
		str[i] = ft_strjoin(ft_strjoin(env->variable, "="), env->value);
		env = env->next;
		i++;
	}
	str[i] = NULL;
	return (str);

}

void ft_unset(t_envir *env,char *cmd)
{
	env = rem_from_list(env, cmd);
}