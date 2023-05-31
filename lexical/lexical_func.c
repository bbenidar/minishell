/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 11:39:12 by bbenidar          #+#    #+#             */
/*   Updated: 2023/05/30 17:10:57 by bbenidar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

static int	ft_strlen_nospace(const char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
    {
        if( str[i] != 34 && str[i] != 39)
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
    while(line[j])
    {
        if(line[j] != 34 && line[j] != 39)
        {
            str[i] = line[j];
            i++;
        }
        j++;
    }
    str[i] = '\0';
    return (str);
}

int check_any_redire(char *str ,t_stack **wrd)
{
    int i;

    i = 0;
   if(str[i] == '>')
   {
    if(str[i+1] == '>')
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
   
  if(str[i] == '<')
   {
    if(str[i+1] == '<')
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
    line = ft_strjoin(str[0], " ");
    while(str[i])
    {
        line = ft_strjoin(line, str[i]);
        line = ft_strjoin(line, " ");
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
    while(src[i])
    {
        if(j == 0)
        {
            wrd->next = ft_my_lstnew(src[i], COMMAND);
            j = 1;
        }   
        else if(!ft_strncmp(src[i], "|", 1))
        {
            wrd->next = ft_my_lstnew("|", PIPE);
            j = 0;
        }
        else if(!ft_strncmp(src[i], "<<", 2) || (!ft_strncmp(src[i], "<", 1)))
        {
            if (!ft_strncmp(src[i], "<<", 2))
                wrd->next = ft_my_lstnew("<<", RED_HER);
            else
                wrd->next = ft_my_lstnew("<", RED_IN);
        }
        else if(!ft_strncmp(src[i], ">>", 2) || (!ft_strncmp(src[i], ">", 1)))
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
    while(list->next)
    {
        if(list->key == RED_APP)
        {
            if(list->next->key != OPTION)
            {
               printf("\033[0;31mERROR :syntax error near unexpected token `|'\033[0m\n");
                return (0);
            }
            list->next->key = FILE_APP;
        }
        else if(list->key == RED_OUT)
        {
            if(list->next->key != OPTION)
            {
               printf("\033[0;31mERROR :syntax error near unexpected token `|'\033[0m\n");
                return (0);
            }
            list->next->key = FILE_OUT;
        }
        else if(list->key == RED_IN)
        {
            if(list->next->key != OPTION)
            {
               printf("\033[0;31mERROR :syntax error near unexpected token `|'\033[0m\n");
                return (0);
            }
            list->next->key = FILE_IN;
        }
        else if(list->key == RED_HER)
        {
            if(list->next->key != OPTION)
            {
               printf("\033[0;31mERROR :syntax error near unexpected token `|'\033[0m\n");
                return (0) ;
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
    while(list->key != 11)
    {
        if(list->key == 2)
            i++;
        list = list->next;
    }
    return (i);
}

char **ft_option(int i)
{
    char **str;

    str = (char **)malloc(sizeof(char) * i);
    return (str);
}

int open_filw_fd(char *word, int key)
{
    int fd;
    if(key == FILE_APP)
        fd = open(word,O_CREAT,O_APPEND);
    else
        fd = open(word,O_CREAT,O_TRUNC);
    return (fd);
}

int ft_her_and_out_file(char *word, int key)
{
    int fd;
    if(key == LIMITER)
        fd = open("/tmp/herdoc",O_CREAT,O_RDWR);
    else
        fd = open(word,O_RDONLY);
    return (fd);
}
t_stack *ft_last_list_get_ready(t_stack *head)
{
    t_last *last;
    t_last *ret;
    int i;
    i = option_len(head);
    last = ft_new_last_list(0);
    while(head)
    {
        
        while(head->key != 11)
        {
            last->option = ft_option(option_len(head));
            if(head->key == 1)
                last->command = head->word;
            if(head->key == 2)
            {
                *last->option = ft_strdup(head->word);
                last->option++;
            }
            if(head->key == 9 || head->key == 10)
                last->input = open_filw_fd(head->word, head->key);
            if(head->key == 7 || head->key == 8)
                last->output = ft_her_and_out_file(head->word,  head->key);
            
                
        }
    }
}

void lexical_function(char *line)
{
    t_stack *head;
    // t_stack *last;
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
    head = split_in_list(str);
    free(str);
    if (!cheking_(head))
        return ;
    while(head)
    {
        printf("wrd :%s key %d\n", head->word, head->key);
        head = head->next;
    }
    // last = ft_last_list_get_ready(head);
    
}



// if key == 1 command if 2 option if 3 pipe if 4 redir
// t_stack *bb;
//bb.word = "ls"
// bb.key = COMMAND;  4 7

// ------------------
// |ls  | 1 | next|
// -----------------

// node1 = ls->COMMAND
// node2 = [ ]->SPACES
// node3 = [-la]->OPTION
// -----------------
// |-la  | 2 | next|
// -----------------

// -----------------
// | |  | 3   | next|
// -----------------


// -----------------
// |wc | 1 | next|
// -----------------

// -----------------
// | > | 4 | next|
// -----------------