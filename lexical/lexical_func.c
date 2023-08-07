/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 11:39:12 by bbenidar          #+#    #+#             */
/*   Updated: 2023/08/07 16:27:33 by bbenidar         ###   ########.fr       */
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
	int i = 0;
	char *str;
	int j;

	j = 0;
	if(!line)
		return (NULL);
	while(line[i])
	{
		if((line[i] == 34 && line[i + 1] == 34)
			|| (line[i] == 39 && line[i + 1] == 39))
		{
			int c = i + 2;
			while(line[c] && line[c] == ' ')
				c++;
			if((line[c] == '|' || line[c] == '\0'))
			{
				line[i] *= -1;
				line[i + 1] *= -1;
			}
		}
		i++;
	}
	i = ft_strlen_nospace(line);
	str = (char *)malloc(sizeof(char) * i + 1);
	if(!str)
		return (NULL);
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
	j = 0;
	while(str[j])
	{
		if(str[j] == 34 * -1 || str[j] == 39 * -1)
			str[j] *= -1;
		j++;
	}
	return (str);
}

char *dell_qots(char *line)
{
	int i = 0;
	char *str;
	int j;

	j = 0;
	if(!line)
		return (NULL);
	i = ft_strlen_nospace(line);
	str = (char *)malloc(sizeof(char) * i + 1);
	if(!str)
		return (NULL);
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
	i = 0;
	char *line;
	if (!str)
		return (NULL);
	line = ft_strdup("");
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
	i = 1;
	char *line;

	if (!str)
		return (NULL);
	if (str && str[0] && !str[1])
		return (ft_strdup(str[0]));
	line = ft_strdup("");
	line = ft_strjoin(line, str[0]);
	while (str && str[i])
	{
		line = ft_strjoin(line, str[i]);
		i++;
	}
	return (line);
}

void ft_free_stack(t_stack **env){

	while(*env)
	{
		free((*env)->word);
		free((*env));
		(*env) = (*env)->next;
	}
}

void ft_free_last(t_last **env){

	while(*env)
	{
		free_tab((*env)->word);
		free((*env));
		(*env) = (*env)->next;
	}
}

t_stack *split_in_list(char *str)
{
	char **src;
	t_stack *wrd;
	t_stack *head = NULL;

	wrd = NULL;
	int i = 0;
	int j = 0;
	src = ft_split(str, ' ');
	if(src)
	{
		wrd = ft_my_lstnew(NULL, 0);
		head = wrd;
		while (src[i])
		{
			if (!ft_strncmp(src[i], "|", 1))
			{
				wrd->word = ft_strdup("|");
				wrd->key = PIPE;
				j = 0;
			}
			else if (!ft_strncmp(src[i], "<<", 2) || (!ft_strncmp(src[i], "<", 1)))
			{
				if (!ft_strncmp(src[i], "<<", 2))
				{
					wrd->word = ft_strdup("<<");
					wrd->key = RED_HER;
				}
				else
				{
					wrd->word = ft_strdup("<");
					wrd->key = RED_IN;
				}
				g_flags.red_flag = 1;
			}
			else if (!ft_strncmp(src[i], ">>", 2) || (!ft_strncmp(src[i], ">", 1)))
			{
				if (!ft_strncmp(src[i], ">>", 2))
				{
					wrd->word = ft_strdup(">>");
					wrd->key = RED_APP;
				}
					
				else
				{
					wrd->word = ft_strdup(">");
					wrd->key = RED_OUT;
				}
				g_flags.red_flag = 1;
					
			}
			else if (j == 0 && g_flags.red_flag != 1)
			{
				wrd->word = ft_strdup(src[i]);
				wrd->key = COMMAND;
				j = 1;
			}
			else
			{
				wrd->word = ft_strdup(src[i]);
				wrd->key = OPTION;
				g_flags.red_flag = 0;
			}
			i++;
			if(src[i])
			{
				wrd->next = ft_my_lstnew(NULL,0);
				wrd = wrd->next;
			}
			
			
		}
		free_tab(src);
	}
	return (head);
}

int cheking_(t_stack *tmp)
{
	t_stack *list;

	list = tmp;
	while (list && list->next)
	{
		if (list->key == RED_APP)
		{
			if (list->next->key != OPTION)
			{
				if(list->next->key == PIPE)
					printf("\033[0;31mERROR :syntax error near unexpected token `>>`\033[0m\n");
				return (0);
			}
			list->next->key = FILE_APP;
		}
		else if (list->key == RED_OUT)
		{
			if (list->next->key != OPTION)
			{
				printf("\033[0;31mERROR :syntax error near unexpected token `<`\033[0m\n");
				return (0);
			}
			list->next->key = FILE_OUT;
		}
		else if (list->key == RED_IN)
		{
			if (list->next->key != OPTION)
			{
				printf("\033[0;31mERROR :syntax error near unexpected token `>'\033[0m\n");
				return (0);
			}
			list->next->key = FILE_IN;
		}
		else if (list->key == RED_HER)
		{
			if (list->next->key != OPTION)
			{
				printf("\033[0;31mERROR :syntax error near unexpected token `<<'\033[0m\n");
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
	free(src);
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
		if (*word == 32 * -1 || *word == 60 * -1 || *word == '\'' * -1 || *word == '\"' * -1)
			*word *= -1;
		word++;
	}
}

volatile sig_atomic_t g_interrupted = 0;

void ft_herd(int sig)
{
	(void)sig;
	close(STDIN_FILENO);
}

int set_non_blocking_mode(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1) return -1;
    return fcntl(fd, F_SETFL, flags | O_NONBLOCK);
}


void	fd_herdoc(int fd[2])
{
	int	fdd;

	fdd = open(ttyname(STDERR_FILENO), O_RDONLY);
	if (fdd == -1)
		return (close_pipe(fd), ft_putendl_fd("Error herdoc_fd", 2));
	close_pipe(fd);
}

int ft_herdoc(t_stack *list, int flag, t_envir *envr)
{
	int fd;
	static int rand;
	char *her;
	char *name;
	char *tty;

	name = ttyname(1);
	tty = ft_strchr(name,'0');
	name = ft_itoa(rand++);
	her = ft_strjoin(ft_strdup(tty),name);
	free(name);
	
	name = ft_strjoin(ft_strdup("/tmp/heredoc"), her);
		fd = open(name, O_CREAT | O_RDWR | O_TRUNC, 0777);
	free(her);
	if(list->next  && (!ft_strcmp(list->next->word, "\"\"") || !ft_strcmp(list->next->word, "\'\'")))
			list->next->word = ft_strdup("");
	signal(SIGINT, ft_herd);
	tty = dell_qots(list->next->word);
	free(list->next->word);
	list->next->word = tty;
	printf("nn : %s\n", list->next->word);
	while (isatty(STDIN_FILENO))
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
			{
				free(her);
				break;
			}	
		}
		if(g_flags.delim_flags == 0)
			her = ft_add_variables(her, envr, 1);
		ft_putstr_fd(her, fd);
		ft_putstr_fd("\n", fd);
		free(her);
	}
	if(g_flags.delim_flags != 0)
		g_flags.delim_flags--;
	signal(SIGINT, ft_sigint);
	if (!isatty(STDIN_FILENO))
		return (free(name), fd_herdoc(&fd), -5);
	if(flag == 0)
	{
		free(list->word);
		list->word = ft_strdup(name);
	}
		
	else if(list->next && list->next->next)
	{
		list->word = list->next->next->word;
		list->key = COMMAND;
		list->next->next->word = ft_strdup("");
	}
	if(list->next)
	{
		free(list->next->word);
		list->next->word = ft_strdup(name);
	 	list->next->key = FILE_IN;
	}
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
	i = 0;
	while (tmp)
	{

		flag = 1;
		// i = option_len(head);
		while (tmp && tmp->key != PIPE)
		{
			if(!i)
			{
				while (tmp)
				{
					if (tmp && (!ft_strcmp(tmp->word, "<<") && tmp->key == RED_HER))
					{
						last->input = ft_herdoc(tmp, flag, envr);
						if (last->input < 0)
						{
							if(last->input == -1)
								perror(tmp->word);
							return (NULL);
						}
						free(tmp->word);
						tmp->word = ft_strdup("");
						tmp->key = OPTION;
					}
					tmp= tmp->next;
				}
				i = 1;
				tmp = head;
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

	return (ret);
}

char *find_value(char *str, t_envir *env)
{
	char *ret;

	ret = ft_strdup("");
	if (str[0] == '?')
			ret = ft_strdup(ft_itoa(g_flags.exit_stat/256));
		while (env)
		{
			if (!ft_strcmp(env->variable, str))
			{
				ret = ft_strjoin(ret, env->value);
				break;
			}
			env = env->next;
		}
	free(str);
	return (ret);
}


void ft_check_delim(char *str)
{
	int i = 0;

	while(str[i])
	{
		if (str[i] == '<' && str[i + 1] == '<')
		{
			i += 2;
			while(str[i] == ' ')
				i++;
			while(str[i] && str[i] != ' ')
			{
				
				if(str[i] == '\"')
					g_flags.delim_flags++;
				if (str[i] == '\"' && str[i+1] == '\"' && str[i + 2] == ' ')
				{
					str[i] *= -1;
					str[i + 1] *= -1;
				}
				if (str[i] == '\'' && str[i+1] == '\'' && str[i + 2] == ' ')
				{
					 str[i] *= -1;
					str[i + 1] *= -1;
				}
				if (str[i] == '$')
					str[i] *= -1;
				i++;
			}
		}
		i++;
	}
	g_flags.delim_flags /= 2;
}

char *ft_add_variables(char *line, t_envir *envr, int f)
{
	int i;
	int j = 0;
	char **src;
	int len = 0;
	if(!f)
		ft_check_delim(line);
	while (line[len])
	{
		if (line[len] && line[len] == ' ')
			line[len] *= -2;
		len++;
	}

	i = 0;
	
	src = ft_split_opera(line, '\"');
	free(line);
	line = merge_str(src);
	free_tab(src);
	src = ft_split_opera(line, '\'');
	free(line);
	line = merge_str(src);
	free_tab(src);
	src = ft_split_opera(line, '/');
	free(line);
	line = merge_str(src);
	free_tab(src);
	src = ft_split_opera(line, '$');
	free(line);
	line = merge_str(src);
	free_tab(src);
	src = ft_split_opera(line, '?');
	free(line);
	line = merge_str(src);
	free_tab(src);
	src = ft_split_opera(line, ' ' * -2);
	free(line);
	line = merge_str(src);
	free_tab(src);
	src = ft_split_opera(line, ' ' * -1);
	free(line);
	line = merge_str(src);
	free_tab(src);
	src = ft_split_opera(line, '<');
	free(line);
	line = merge_str(src);
	free_tab(src);
	src = ft_split(line, ' ');
	
	while (src && src[i])
	{
		if (src[i + 1] && (!ft_strcmp(src[i], "<<") ||  !ft_strcmp(src[i], "\'")) )
		{
			while(src[i + 1] && (src[i + 1][0] == (' ' * -2) || src[i + 1][0] == '\"' || src[i + 1][0] == '\''))	
					i++;
			if(src[i + 1] && src[i + 1][0] == '$' && !f)
				src[i + 1][0] *= -1;
				
		}
		else if (!ft_strcmp(src[i], "$") && (src[i + 1]))
		{
			if ((src[i + 1][0] != ' ' * -2 && src[i + 1][0] != ' ' * -1 && src[i + 1][0] != '\"'  && src[i + 1][0] != '\''))
				src[i + 1] = find_value(src[i + 1], envr);
			if (!ft_strcmp(src[i + 1], ""))
			{
				free(src[i]);
				src[i] = ft_strdup("");
			}
				
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
	free(line);
	line = merge_tab(src);
	free_tab(src);
	src = ft_split(line, '$');
	free(line);
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
	free_tab(src);
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
	free(str);
	str = merge_str(src);
	free_tab(src);
	src = ft_split_opera(str, '<');
	free(str);
	str = merge_str(src);

	free_tab(src);
	head = split_in_list(str);
	free(str);
	if (!cheking_(head))
	{
		g_flags.exit_stat = 66048;
		return;
	}
	last = ft_last_list_get_ready(head, envr);
		if(!last)
			return ;
		if(last->word)
			ft_execution(last, env, envr);
		else
		{
			printf("minishell: :command not found\n");
			g_flags.exit_stat = 127 * 256;
		}
	ft_free_stack(&head);
	ft_free_last(&last);
            
	}