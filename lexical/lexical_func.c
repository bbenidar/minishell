/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakarkal <sakarkal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 11:39:12 by bbenidar          #+#    #+#             */
/*   Updated: 2023/07/06 13:37:49 by sakarkal         ###   ########.fr       */
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
    while(list && (list->key != 11))
    {
        if(list->key == 2 || list->key == 1)
            i++;
        list = list->next;
    }
    return (i);
}

// char **ft_add_tab(char **str, char *src)
// {
//     char **tab;
//     int i = 0;

//     while(str[i])
//         i++;
//     tab = malloc(sizeof(char *) * i + 1);
//     tab[i] = strdup(src);

// }

void ft_option(t_stack *list,int i, t_last *str)
{
    t_stack *tmp;
    char *src = ft_strdup("");
    int j;

    j = 0;
    tmp = list;

    str->word = (char **)malloc(sizeof(char) * i + 1);
    if( !str->word)
    {
        printf("allocat error");
        exit(1);
    }
        
    while(tmp && tmp->key != PIPE)
    {
        if(tmp->key == COMMAND  || tmp->key == OPTION)
        {
            src = ft_strjoin(src, tmp->word);
            src = ft_strjoin(src, "&");
        }  
        tmp = tmp->next;
        j++;
    }
    str->word = ft_split(src, '&');
}

int open_fd_out(char *word, int key)
{
    int fd;
    if(key == FILE_APP)
        fd = open(word,O_CREAT | O_APPEND, 0777);
    else
        fd = open("txtxtx",O_CREAT | O_TRUNC, 0777);
        
    return (fd);
}

void ft_herdoc(t_stack *list)
{
    int fd;
    char *her;

    fd = open("/tmp/here",O_CREAT | O_RDWR, 0777);
    while(1)
    {
        her = readline("> ");
        if (!ft_strcmp(her, list->next->word))
            break;
        ft_putstr_fd(her, fd);
        ft_putstr_fd("\n", fd);
    }
    list->next->key = FILE_IN;
}

void ft_check_for_herdoc(t_stack *list)
{
    while(list)
    {
        if (list->key == RED_HER)
            ft_herdoc(list);
        list = list->next;
    }
} 
t_last *ft_last_list_get_ready(t_stack *head)
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

    ft_check_for_herdoc(tmp2);
    flag = 1;
    i = option_len(head);
    last = ft_new_last_list(tmp->word);
    ret = last;

   while(tmp)
    {
        
        flag = 1;
        i = option_len(head);
        while( tmp && tmp->key != PIPE)
        {
            
            if(flag == 1)
            {
                tmp3 = tmp;
               ft_option(tmp, i, last);
               flag = 0;
               tmp = tmp3;
            }
            if(tmp->key == FILE_IN )
                last->input = open(tmp->word, O_RDONLY, 0777);
            if(tmp->key == FILE_OUT || tmp->key == FILE_APP)
                last->input = open_fd_out(tmp->word, tmp->key);
                
            tmp = tmp->next;
        }
        
        if(tmp && tmp->key == PIPE)
        {
            tmp = tmp->next;
            last->next = ft_new_last_list(tmp->word);
            last = last->next;
        }
            
    }
    i = 0;
    while(ret)
    {
        i =0;
        printf("________________________________________________________________________________________________________\n");
        while(ret->word[i])
        {
            
            printf("|  command : %s ", ret->word[i]);
            i++;
        }
        printf("| fd input : %d   | fd out : %d | | fd herdok : %d |\n", ret->input, ret->output, ret->input_heredoc);
        // the input file takes the file descriptor of the out put file, must fix
        // when getting a input file , the input file variable gets a negative value, must look into it;
        // the arguments should be specified as command arguments not as commands
        // the heredoc does not get a specifier that indicates that there is a heredoc
        ret = ret->next;
    }
    return (ret);
}

void lexical_function(char *line)
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
    head = split_in_list(str);
    free(str);
    if (!cheking_(head))
        return ;
    // while(head)
    // {
    //     printf("wrd :%s key %d\n", head->word, head->key);
    //     head = head->next;
    // }
    last = ft_last_list_get_ready(head);
    
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