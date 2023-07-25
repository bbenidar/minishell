/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 11:39:12 by bbenidar          #+#    #+#             */
/*   Updated: 2023/07/25 22:13:32 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int ft_strlen_nospace(const char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] != 34 && str[i] != 39)
			j++;
		i++;
	}

	return (j);
}

char *dell_space(char *line)
{
	int i;
	char *str;
	int j;

	j = 0;
	i = ft_strlen_nospace(line);
	str = (char *)malloc(sizeof(char) * i);
	i = 0;
	while (line[j])
	{
		if (line[j] != 34 && line[j] != 39)
		{
			str[i] = line[j];
			i++;
		}
		j++;
	}
	str[i] = '\0';
	return (str);
}

int check_any_redire(char *str, t_stack **wrd)
{
	int i;

	i = 0;
	if (str[i] == '>')
	{
		if (str[i + 1] == '>')
		{
			printf("kksks\n");
			(*wrd)->next = ft_my_lstnew(">>", RED_APP);
			return (2);
		}
		else
		{
			(*wrd)->next = ft_my_lstnew(">", RED_OUT);
			return (1);
		}
	}

	if (str[i] == '<')
	{
		if (str[i + 1] == '<')
		{
			(*wrd)->next = ft_my_lstnew("<<", RED_HER);
			return (2);
		}
		else
		{
			(*wrd)->next = ft_my_lstnew("<", RED_IN);
			return (1);
		}
	}
	return (0);
}

char *merge_str(char **str)
{
	int i;
	i = 1;
	char *line;
	if (!str)
		return (NULL);
	line = ft_strjoin(str[0], " ");
	while (str[i])
	{
		line = ft_strjoin(line, str[i]);
		line = ft_strjoin(line, " ");
		i++;
	}
	return (line);
}

char *merge_tab(char **str)
{
	int i;
	i = 2;
	char *line;

	if (!str)
		return (NULL);
	if (str && str[0] && !str[1])
		return (ft_strdup(str[0]));
	line = ft_strjoin(str[0], str[1]);
	while (str && str[i])
	{
		line = ft_strjoin(line, str[i]);
		i++;
	}
	return (line);
}

t_stack *split_in_list(char *str)
{
	char **src;
	t_stack *wrd;
	t_stack *head;

	wrd = NULL;
	int i = 0;
	int j = 1;
	src = ft_split(str, ' ');
	wrd = ft_my_lstnew(src[0], COMMAND);
	i++;
	head = wrd;
	while (src[i])
	{
		if (j == 0)
		{
			wrd->next = ft_my_lstnew(src[i], COMMAND);
			j = 1;
		}
		else if (!ft_strncmp(src[i], "|", 1))
		{
			wrd->next = ft_my_lstnew("|", PIPE);
			j = 0;
		}
		else if (!ft_strncmp(src[i], "<<", 2) || (!ft_strncmp(src[i], "<", 1)))
		{
			if (!ft_strncmp(src[i], "<<", 2))
				wrd->next = ft_my_lstnew("<<", RED_HER);
			else
				wrd->next = ft_my_lstnew("<", RED_IN);
		}
		else if (!ft_strncmp(src[i], ">>", 2) || (!ft_strncmp(src[i], ">", 1)))
		{
			if (!ft_strncmp(src[i], ">>", 2))
				wrd->next = ft_my_lstnew(">>", RED_APP);
			else
				wrd->next = ft_my_lstnew(">", RED_OUT);
		}
		else
			wrd->next = ft_my_lstnew(src[i], OPTION);

		wrd = wrd->next;
		i++;
	}

	return (head);
}

int cheking_(t_stack *tmp)
{
	t_stack *list;

	list = tmp;
	while (list->next)
	{
		if (list->key == RED_APP)
		{
			if (list->next->key != OPTION)
			{
				printf("\033[0;31mERROR :syntax error near unexpected token `|'\033[0m\n");
				return (0);
			}
			list->next->key = FILE_APP;
		}
		else if (list->key == RED_OUT)
		{
			if (list->next->key != OPTION)
			{
				printf("\033[0;31mERROR :syntax error near unexpected token `|'\033[0m\n");
				return (0);
			}
			list->next->key = FILE_OUT;
		}
		else if (list->key == RED_IN)
		{
			if (list->next->key != OPTION)
			{
				printf("\033[0;31mERROR :syntax error near unexpected token `|'\033[0m\n");
				return (0);
			}
			list->next->key = FILE_IN;
		}
		else if (list->key == RED_HER)
		{
			if (list->next->key != OPTION)
			{
				printf("\033[0;31mERROR :syntax error near unexpected token `|'\033[0m\n");
				return (0);
			}
			list->next->key = LIMITER;
		}

		list = list->next;
	}
	return (1);
}
int option_len(t_stack *list)
{
	int i;

	i = 0;
	while (list && (list->key != 11))
	{
		if (list->key == 2 || list->key == 1)
			i++;
		list = list->next;
	}
	return (i);
}

void ft_remove_gv(char *str)
{
	int i = 0;

	while (str[i])
	{
		if (str[i] == 32 * -1)
			str[i] = 32;
		i++;
	}
}

void ft_option(t_stack *list, int i, t_last *str)
{
	t_stack *tmp;
	char *src = ft_strdup("");
	int j;

	j = 0;
	tmp = list;

	str->word = (char **)malloc(sizeof(char) * i + 1);
	if (!str->word)
	{
		printf("allocat error");
		exit(1);
	}

	while (tmp && tmp->key != PIPE)
	{
		if (tmp->key == COMMAND || tmp->key == OPTION)
		{
			src = ft_strjoin(src, tmp->word);
			src = ft_strjoin(src, "&");
		}
		tmp = tmp->next;
		j++;
	}
	ft_remove_gv(src);
	str->word = ft_split(src, '&');
}

int open_fd_out(char *word, int key)
{
	int fd;
	if (key == FILE_APP)
		fd = open(word, O_CREAT | O_RDWR | O_APPEND, 0777);
	else
		fd = open(word, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (fd < 0)
	{
		perror("minishell");
		return (fd);
	}

	return (fd);
}

void return_space_to_real_value(char *word)
{
	while (*word)
	{
		if (*word == 32 * -1 || *word == 60 * -1)
			*word *= -1;
		word++;
	}
}

int ft_herdoc(t_stack *list, int flag, t_envir *envr)
{
	int fd;
	static int rand;
	char *her;
	char *name;

	her = ft_strjoin(strchr(ttyname(0),'0'),ft_itoa(rand++));
	name = ft_strjoin("/tmp/heredoc", her);
		fd = open(name, O_CREAT | O_RDWR | O_TRUNC, 0777);
	while (1)
	{
		her = readline("> ");
		if (!her)
		{
			break;
		}
		
		if (!ft_strlen(her) && !list->next)
			break;
		else if (list->next)
		{
			
			return_space_to_real_value(list->next->word);
			if (!ft_strcmp(her, list->next->word))
				break;
				
		}
		her = ft_add_variables(her, envr);
		ft_putstr_fd(her, fd);
		ft_putstr_fd("\n", fd);
	}
	if(flag == 0)
		list->word = ft_strdup(name);
	else if(list->next->next)
	{
		list->word = list->next->next->word;
		list->next->next->word = ft_strdup("");
	}
		
	free(list->next->word);
	// printf("gg:1 %s\n", list->next->word);
	list->next->word = ft_strdup(name);
	list->next->key = FILE_IN;
	// printf("gg: %d\n", fd);
	free(name);
	return (fd);
}

t_last *ft_last_list_get_ready(t_stack *head, t_envir *envr)
{
	t_last *last;
	t_last *ret;
	t_stack *tmp;
	t_stack *tmp2;
	t_stack *tmp3;
	tmp = head;
	tmp2 = head;
	int i;
	int flag;

	flag = 1;
	i = option_len(head);
	last = ft_new_last_list();
	ret = last;

	while (tmp)
	{

		flag = 1;
		i = option_len(head);
		while (tmp && tmp->key != PIPE)
		{
			if (tmp && ( !ft_strcmp(tmp->word, "<<") || tmp->key == RED_HER))
			{
				// printf("wrd : %s \n", tmp->word);
				last->input = ft_herdoc(tmp, flag, envr);
				if (last->input < 0)
				{
					perror(tmp->word);
					return (NULL);
				}
				tmp->key = OPTION;
			}
			if (tmp && flag == 1 && ft_strcmp(tmp->word, "<<") )
			{
				tmp3 = tmp;
				ft_option(tmp, i, last);
				flag = 0;
				tmp = tmp3;
			}
			if (tmp->key == FILE_IN)
			{
				last->input = open(tmp->word, O_RDONLY, 0777);
				if (last->output < 0)
				{
					last->output = 1;
					last->input = 0;
					// free_tab here(last->word)
					last->word = NULL;
					perror(tmp->word);
					while (tmp && tmp->key != PIPE)
						tmp = tmp->next;
					if (tmp && tmp->next != NULL)
						tmp = tmp->next;
					break;
				}
			}

			if (tmp->key == FILE_OUT || tmp->key == FILE_APP)
				last->output = open_fd_out(tmp->word, tmp->key);
			if(last->output < 0)
			{
				return(NULL);
			}
			

			tmp = tmp->next;
		}
		if (!tmp || tmp->next == NULL)
			break;
		if (tmp && tmp->key == PIPE)
		{
			tmp = tmp->next;
			last->next = ft_new_last_list();
			last = last->next;
		}
	}
	i = 0;

	return (ret);
}

char *find_value(char *str, t_envir *env)
{
	char *ret;

	ret = ft_strdup("");
	if (str[0] == '?')
			ret = ft_strdup(ft_itoa(exit_stat/256));
		while (env)
		{
			// printf("str : %s \n", str);
			if (!ft_strcmp(env->variable, str))
			{
				ret = ft_strjoin(ret, env->value);
				break;
			}
			env = env->next;
		}
	
	return (ret);
}

// char *merge_tab(char **str)
// {
//     int i;
//     i = 2;
//     char *line;
//     if(str[0] &&!str[1])
//         return(ft_strdup(str[0]));
//     line = ft_strjoin(str[0], str[1]);
//     while(str[i])
//     {
//         line = ft_strjoin(line, str[i]);
//         i++;
//     }
//     return (line);
// }

char *ft_add_variables(char *line, t_envir *envr)
{
	int i;
	int j = 0;
	char **src;
	int len = 0;
	while (line[len])
	{
		if (line[len] && line[len] == ' ')
			line[len] *= -2;
		len++;
	}

	i = 0;
	src = ft_split_opera(line, '\"');
	line = merge_str(src);
	src = ft_split_opera(line, '\'');
	line = merge_str(src);
	
	src = ft_split_opera(line, '$');
	line = merge_str(src);
	src = ft_split_opera(line, '?');
	line = merge_str(src);
	src = ft_split_opera(line, ' ' * -2);
	line = merge_str(src);
	src = ft_split_opera(line, '<');
	line = merge_str(src);
	src = ft_split(line, ' ');


	while (src && src[i])
	{
		
		if (!ft_strcmp(src[i], "<<") )
		{
			while(src[i + 1][0] == (' ' * -2))
				i++;
			if(src[i + 1][0] == '$')
				src[i + 1][0] *= -1;
			// printf("HHHH %s\n", (src[i + 1]));
		}
		else if (!ft_strcmp(src[i], "$") && (src[i + 1]))
		{
			if ((src[i + 1][0] != ' ' * -2 && src[i + 1][0] != ' ' * -1 && src[i + 1][0] != '\"'  && src[i + 1][0] != '\''))
				src[i + 1] = find_value(src[i + 1], envr);
			if (!ft_strcmp(src[i + 1], ""))
				src[i] = ft_strdup("");
		}
		i++;
	}

	i = 0;
	while (src && src[i])
	{
		if (src[i][0] == '$')
		{
			j = -1;
			if (!src[i + 1])
			{
				while (src[i][++j])
				{
					if(src[i][j] != '?')
						src[i][j] *= -1;
				}
			}

			else if (!ft_strcmp(src[i + 1], "\"") || !ft_strcmp(src[i + 1], "\'")|| src[i][1] == '$' || src[i + 1][0] == 32 * -2)
			{
				while (src[i][++j])
					src[i][j] *= -1;
			}
		}
		i++;
	}
	line = merge_tab(src);

	src = ft_split(line, '$');
	line = merge_tab(src);

	i = 0;
	while (line && line[i])
	{
		if (line[i] == 32 * -2)
			line[i] = 32;
		if (line[i] == '$' * -1)
			line[i] = '$';
		i++;
	}

	// src = ft_split(line, ' ');
	// line = merge_str(src);
	// ft_free_tab() need free tab function
	// printf("line : %s\n", line);
	return (line);
}

void lexical_function(char *line, char **env, t_envir *envr)
{
	t_stack *head;
	t_last *last;
	char *str;
	char **src;
	int i;
	int redir;
	i = 0;
	redir = 0;

	str = dell_space(line);
	src = ft_split_opera(str, '|');
	free(str);
	str = merge_str(src);
	free_tab(src);
	src = ft_split_opera(str, '>');
	str = merge_str(src);
	free_tab(src);
	src = ft_split_opera(str, '<');
	str = merge_str(src);
	// printf("line : %s\n", str);

	head = split_in_list(str);
	free(str);
	if (!cheking_(head))
		return;
	// printf("line : %s\n", line);
	last = ft_last_list_get_ready(head, envr);
	if(!last)
		return ;
	// while(last)
	// {
	//     i =0;
	//     printf("________________________________________________________________________________________________________\n");
	//     while(last->word && last->word[i])
	//     {

	//         printf("|  command : %s ", last->word[i]);
	//         i++;
	//     }
	//     printf("| fd input : %d   | fd out : %d |\n", last->input, last->output);
	//     last = last->next;
	// }
	ft_execution(last, env, envr);
}