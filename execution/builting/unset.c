
#include"../../minishell.h"

t_envir *rem_from_list(t_envir *env, char *cmd) {
    t_envir *tmp;
    t_envir *ret;

    if (!ft_strcmp(env->variable, cmd)) {
        ret = env->next;
        return ret;
    }

    ret = env;
    while (env->next) {
        if (!ft_strcmp(env->next->variable, cmd)) {
            tmp = env->next;
            env->next = env->next->next;
            return ret;
        }
        env = env->next;
    }

    return ret;
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
	if(!str)
		return (NULL);
	if(g_flags.grbg)
	{
		g_flags.grbg->next = ft_get_new_node();
		g_flags.grbg = g_flags.grbg->next;
	}
	else
	{
		g_flags.grbg = ft_get_new_node();
		g_flags.grbg_head = g_flags.grbg;
	}
	g_flags.grbg->collector = str;
	while(env)
	{
		str[i] = ft_strjoin(ft_strjoin(env->variable, "="), env->value);
		env = env->next;
		i++;
	}
	str[i] = NULL;
	return (str);

}

void ft_unset(t_envir **env,char *cmd)
{
	*env = rem_from_list(*env, cmd);
}