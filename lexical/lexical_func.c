/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 11:39:12 by bbenidar          #+#    #+#             */
/*   Updated: 2023/07/07 16:10:34 by bbenidar         ###   ########.fr       */
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

//_______________________random number string __________________________//
// char *ft_rand()
// {
//     char *rand;
//     int fd = open("/dev/urandom", O_RDONLY);
//     unsigned int randomNumber;
//     if (fd < 0) {
//         printf("Failed to open /dev/urandom\n");
//         return (NULL);
//     }

//     unsigned int result = read(fd, &randomNumber, sizeof(randomNumber));
//     close(fd);
//     if (result < 0) {
//         printf("Failed to read /dev/urandom\n");
//         return (NULL);
//     }
//     rand = ft_itoa(randomNumber);
//     return (rand);
// }
//_________________________________________________________________________//

void return_space_to_real_value(char *word)
{
    while(*word)
    {
        if (*word == 32 * -1)
            *word = 32;
        word++;
    }
}

int ft_herdoc(t_stack *list)
{
    int fd;
    static int rand;
    char *her;
    char *name;

    her = ft_itoa(rand++);
    name = ft_strjoin("/tmp/heredoc", her);
    fd = open(name, O_CREAT | O_RDWR, 0777);
    while(1)
    {
        her = readline("> ");
        if(!ft_strlen(her) && !list->next)
            break ;
        else if (list->next)
        {
            return_space_to_real_value(list->next->word);
            printf("%s hhhh\n", list->next->word);
            if(!ft_strcmp(her, list->next->word))
                break;
        }
        ft_putstr_fd(her, fd);
        ft_putstr_fd("\n", fd);
    }
    // printf("%d hhhh\n", fd);
    return(fd);
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
            {
                last->input = open(tmp->word, O_RDONLY, 0777);
                if(last->input < 0)
                {
                    printf("\033[0;31mERROR : %s: No such file or directory\033[0m\n", tmp->word);
                    return (NULL);
                }
                    
            }
                
            if(tmp->key == FILE_OUT || tmp->key == FILE_APP)
                last->output = open_fd_out(tmp->word, tmp->key);
            if(tmp->key == RED_HER)
                last->output = ft_herdoc(tmp);
                
                
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
        printf("| fd input : %d   | fd out : %d |\n", ret->input, ret->output);
        // the input file takes the file descriptor of the out put file, must fix
        // when getting a input file , the input file variable gets a negative value, must look into it;
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