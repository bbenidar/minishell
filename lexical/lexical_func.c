/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: messoufi <messoufi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 11:39:12 by bbenidar          #+#    #+#             */
/*   Updated: 2023/05/28 16:26:23 by messoufi         ###   ########.fr       */
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

t_stack	*ft_my_lstnew(char *content, int key)
{
	t_stack	*n;

	n = (t_stack *)malloc(sizeof(*n));
	if (!n)
		return (0);
	n->word = content;
    n->key = key;
	n -> next = NULL;
	return (n);
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

int ft_check_foro(char *str)
{
    int i = 0;

    if(str[i] == '-' && str[i+1] == '\0')
        return (0);
    else
        return (1);
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
    printf("%d : %s\n",i+1, src[i]);
    i++;
    head = wrd;
    while(src[i])
    {
        printf("%d : %s\n",i+1, src[i]);
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
        else if(!ft_strncmp(src[i], "<<", 2))
        {
            wrd->next = ft_my_lstnew("<<", RED_HER);
            j = 0;
        }
        else if(!ft_strncmp(src[i], ">>", 2) || (!ft_strncmp(src[i], ">", 1)))
        {
            if (!ft_strncmp(src[i], ">>", 2))
                wrd->next = ft_my_lstnew(">>", FILE_IN);
            else
                wrd->next = ft_my_lstnew(">", RED_APP);
            j = 0;
        }
        else
            wrd->next = ft_my_lstnew(src[i], OPTION);
        wrd = wrd->next;
        i++;
    }

return (head);
}
void lexical_function(char *line)
{
    t_stack *head;
    char *str;
    char **src;
    int i;
    // int j;
    // int start;
    int redir;
    // int end;
    
    i = 0;
    redir = 0;
    
  
    
    str = dell_space(line);
    src = ft_split_opera(str, '|');
    free(str);
    str = merge_str(src);
    free_tab(src);
    src = ft_split_opera(str, '>');
    str = merge_str(src);
    head = split_in_list(str);
    while(head)
    {
        printf("wrd :%s key %d\n", head->word, head->key);
        head = head->next;
    }
    
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