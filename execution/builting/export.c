#include "../../minishell.h"

t_envir *return_back_ptr(t_envir *env)
{
	while (env->next)
		env = env->next;
	return (env);
}

void	ft_env_ex(t_envir *a)
{
	while (a)
	{
		printf("declare -x %s=\"%s\"\n", a->variable, a->value);
		a = a->next;
	}
}

void ft_export(t_envir *env, char **cmd)
{
	int i = 0;
	int j = 0;
	char **str;
	t_envir *tmp;
	tmp = return_back_ptr(env);
	if (!cmd[1])
	{
		ft_env_ex(env);
		return;
	}
	cmd++;
	tmp->next = creat_env_list();
	tmp = tmp->next;
	while (cmd[i])
	{
		tmp->value = ft_strdup("");
		j = 0;
		str = ft_split(cmd[i], '=');
		tmp->variable = str[j];
		j++;
		if (str[j + 1])
		{
			while (str[j])
			{
				tmp->value = ft_strjoin(ft_strjoin(str[j], "="), str[j]);
				j++;
			}
		}
		else if (str[j])
			tmp->value = ft_strdup(str[j]);
		i++;
		if (cmd[i])
		{
			tmp->next = creat_env_list();
			tmp = tmp->next;
		}
	}
}