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

t_envir *sort_env(t_envir *env)
{
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



char *ft_get_variable(char *str, int *i)
{
	char *ret;
	int j = *i;

	while(str[j] && str[j] != '=')
		j++;
	*i = j;
	ret = malloc(sizeof(char) * j + 1);
    if(g_flags.col)
	{
		g_flags.col->next = ft_get_new_node();
		g_flags.col = g_flags.col->next;
	}
	else
		g_flags.col = ft_get_new_node();
	g_flags.col->collecter = ret;
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


int variable_exists(t_envir *env, char *variable) {
    t_envir *tmp = env;
    while (tmp) {
        if (tmp->variable && ft_strcmp(tmp->variable, variable) == 0) {
            return (1);
        }
        tmp = tmp->next;
    }
    return (0);
}

void ft_export(t_envir *env, char **cmd) {
    int i = 0;
    int j = 0;
	
    t_envir *tmp;
    tmp = return_back_ptr(env);
    if (!cmd[1]) {
        ft_env_ex(env);
        return;
    }
    cmd++;
    if (!variable_exists(env, ft_get_variable(cmd[i], &j)))
    {
        tmp->next = creat_env_list();
        tmp = tmp->next;
    }
    while (cmd[i]) {
        if(!ft_strcmp(cmd[i], "PATH"))
            g_flags.path_fl = 0;
        if (variable_exists(env, ft_get_variable(cmd[i], &j))) {
            t_envir *existing = env;
            while (existing) {
                if (ft_strcmp(existing->variable, ft_get_variable(cmd[i], &j)) == 0) {
                    if (cmd[i][j] == '=') {
                        j++;
                        if (cmd[i][j]) {
                            free(existing->value);
                            existing->value = ft_get_value(cmd[i] + j);
                        }
                    }
                    break;
                }
                existing = existing->next;
            }
        } else {
            tmp->value = ft_strdup("");
            j = 0;
            tmp->variable = ft_get_variable(cmd[i], &j);
            if (cmd[i][j] == '=') {
                tmp->equal = ft_strdup("=");
                j++;
                if (cmd[i][j]) {
                    tmp->value = ft_get_value(cmd[i] + j);
                }
            } else {
                tmp->value = NULL;
                tmp->equal = NULL;
            }
            if (cmd[i + 1]) {
                t_envir *new_node = creat_env_list();
                tmp->next = new_node;
                tmp = new_node;
            }
        }
        i++;
    }
}