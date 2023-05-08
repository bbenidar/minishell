/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenidar <bbenidar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 11:39:12 by bbenidar          #+#    #+#             */
/*   Updated: 2023/05/07 17:58:36 by bbenidar         ###   ########.fr       */
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

void lexical_function(char *line)
{
    t_stack *wrd;
    t_stack *head;
    char *str;
    char **src;
    int i;
    int j;
    int start;
    int redir;
    int end;
    
    i = 0;
    redir = 0;
    
    head = ft_my_lstnew(0, 0);
    wrd = head;
    str = dell_space(line);
    src = ft_split_opera(str);
    free(str);
    
    while(src[i])
    {
        j = 0;
        while(src[i][j])
        {
            while (src[i][j] == ' ' || src[i][j] == '\t')
                j++;
            if(src[i][j])
                start = j;
            if(src[i][j] == '|')
            { 
                wrd = wrd->next;
                printf("ana hna\n");
                wrd->next = ft_my_lstnew("|", PIPE);
                    printf("ana hna 2:  %s | key : %d\n", head->word, head->key);

                ;
                j++;
            }
            while (src[i][j] && (src[i][j] != ' ' && src[i][j] != '\t'))
            {
                j++;
                end = j;
            }
           wrd->word = ft_substr(src[i], start, end - start);
           wrd->key = COMMAND;
           while(src[i][j])
           {
            redir = 0;
            while (src[i][j] == ' ' || src[i][j] == '\t')
                j++;
            if(src[i][j] == '>' || (src[i][j] == '<'))
            {
                printf("hna : \n");
                redir = check_any_redire(src[i] + j, &wrd);
            }
                
            if (redir)
                j += redir;
            start = j;
            while (src[i][j]!= '\0' && (src[i][j] != ' ' || src[i][j] != '\t'))
            {
                j++; 
                end = j;
            }
            if (j != start)
                wrd->next = ft_my_lstnew(ft_substr(src[i], start, end - start), FILE_IN);
            j++; 
           }
           j++;      
        }
        wrd = wrd->next;
        //   printf("src : %s\n", src[i]);
        i++;
    }
    
    while(head)
    {
        printf("wrd : %s | key : %d\n", head->word, head->key);
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