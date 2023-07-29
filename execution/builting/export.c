#include "../../minishell.h"

t_envir *return_back_ptr(t_envir *env)
{
	while (env->next)
		env = env->next;
	return (env);
}
void ft_swap_node(t_envir *list) {
    char *tmp_value = list->value;
    char *tmp_variable = list->variable;
    char *tmp_equal = list->equal;

    list->value = list->next->value;
    list->variable = list->next->variable;
    list->equal = list->next->equal;

    list->next->value = tmp_value;
    list->next->variable = tmp_variable;
    list->next->equal = tmp_equal;
}

int ft_strcasecmp(const char *s1, const char *s2) {
    while (*s1 && *s2) {
        unsigned char c1 = (unsigned char)ft_tolower(*s1);
        unsigned char c2 = (unsigned char)ft_tolower(*s2);

        if (c1 != c2) {
            return c1 - c2;
        }

        s1++;
        s2++;
    }

    return *s1 - *s2;
}

t_envir *sort_env(t_envir *env) {
    t_envir *tmp = NULL;
    int swapped = 1;

    if (!env)
        return NULL;

    while (swapped) {
        swapped = 0;
    t_envir *ptr1 = env;

        while (ptr1->next != tmp) {
            if (ft_strcasecmp(ptr1->variable, ptr1->next->variable) > 0) {
                ft_swap_node(ptr1);
                swapped = 1;
            }

            ptr1 = ptr1->next;
        }

        tmp = ptr1;
    }

    return env;
}

void	ft_env_ex(t_envir *a)
{
	t_envir *sorted_exp;

	sorted_exp = sort_env(a);
	while (a)
	{
		if(a->equal != NULL)
		{
			if(a->value != NULL)
				printf("declare -x %s=\"%s\"\n", a->variable, a->value);
			else
				printf("declare -x %s=\"\"\n", a->variable);
		}
		else
			printf("declare -x %s\n", a->variable);
			
		a = a->next;
	}
}

char *ft_get_variable(char *str, int *i)
{
	char *ret;
	int j = *i;

	while(str[j] && str[j] != '=')
		j++;
	*i = j;
	printf("j : %d i : %d\n", j, *i);
	ret = malloc(sizeof(char) * j + 1);
	j = 0;
	while(j < *i)
	{
		ret[j] = str[j];
		j++;
	}
	ret[j] = 0;
	
	return (ret);
	
}
char *ft_get_value(char *str)
{
	// char *ret;
	// int j = 0;
	// int tmp = i;

	// while(str[i])
	// {
	// 	j++;
	// 	i++;
	// }
		
	// ret = malloc(sizeof(char) * j + 1);
	// j = 0;
	// while(str[tmp])
	// {
	// 	ret[j++] = str[tmp++];
	// }
	// ret[j] = 0;
	return (ft_strdup(str));
	
}

void ft_export(t_envir *env, char **cmd)
{
	int i = 0;
	int j = 0;
	// char **str;

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
		// str = ft_split_opera(cmd[i], '=');
		tmp->variable = ft_get_variable(cmd[i] , &j);
		printf("HHH : %s\n",tmp->variable );
		if(cmd[i][j] == '=')
		{
			tmp->equal = ft_strdup("=");
			j++;
			if(cmd[i][j])
				tmp->value= ft_get_value(cmd[i] + j);
		}
		else{
			tmp->value= NULL;
			tmp->equal = NULL;
		}
			printf("val %s | ea %s | \n", tmp->value,tmp->equal),
		// j++;
		// if (str[j] && str[j + 1])
		// {
		// 	printf("iiii: %s\n", str[j]);
		// 	while (str[j])
		// 	{
		// 		tmp->value = ft_strjoin(ft_strjoin(str[j], "="), str[j]);
		// 		j++;
		// 	}
		// }
		// else if (str[j])
		// 	tmp->equal = ft_strdup(str[j]);
		// else
		// 	tmp->equal = NULL;
		i++;
		if (cmd[i])
		{
			tmp->next = creat_env_list();
			tmp = tmp->next;
		}
	}
}