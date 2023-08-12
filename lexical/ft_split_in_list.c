/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_in_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakarkal <sakarkal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 06:02:04 by bbenidar          #+#    #+#             */
/*   Updated: 2023/08/12 17:50:57 by sakarkal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_stack_element(t_stack *element, char *word, int key)
{
	element->word = ft_strdup(word);
	element->key = key;
}

void	while_process_split_2(char **src, int i, t_stack *wrd, int j)
{
	if (!ft_strncmp(src[i], ">>", 2)
		|| (!ft_strncmp(src[i], ">", 1)))
	{
		if (!ft_strncmp(src[i], ">>", 2))
			create_stack_element(wrd, ">>", RED_APP);
		else
			create_stack_element(wrd, ">", RED_OUT);
		g_flags.red_flag = 1;
	}
	else if (j == 0 && g_flags.red_flag != 1)
	{
		create_stack_element(wrd, src[i], COMMAND);
		j = 1;
	}
	else
	{
		create_stack_element(wrd, src[i], OPTION);
		g_flags.red_flag = 0;
	}
}

void	while_process_split(char **src, int i, t_stack *wrd, int j)
{
	if (!ft_strncmp(src[i], "|", 1))
	{
		create_stack_element(wrd, "|", PIPE);
		j = 0;
	}
	else if (!ft_strncmp(src[i], "<<", 2)
		|| (!ft_strncmp(src[i], "<", 1)))
	{
		if (!ft_strncmp(src[i], "<<", 2))
			create_stack_element(wrd, "<<", RED_HER);
		else
			create_stack_element(wrd, "<", RED_IN);
		g_flags.red_flag = 1;
	}
	else
		while_process_split_2(src, i, wrd, j);
}

t_stack	*create_word_list(char **src)
{
	t_stack	*wrd;
	t_stack	*head;
	int		i;
	int		j;

	i = 0;
	j = 0;
	wrd = ft_my_lstnew(NULL, 0);
	head = wrd;
	if (src)
	{
		while (src[i])
		{
			while_process_split(src, i, wrd, j);
			i++;
			if (src[i])
			{
				wrd->next = ft_my_lstnew(NULL, 0);
				wrd = wrd->next;
			}
		}
		free_tab(src);
	}
	return (head);
}

t_stack	*split_in_list(char *str)
{
	char	**src;
	t_stack	*head;
	t_stack	*wrd;
	int		i;
	int		j;

	head = NULL;
	wrd = NULL;
	i = 0;
	j = 0;
	src = ft_split(str, ' ');
	head = create_word_list(src);
	return (head);
}
