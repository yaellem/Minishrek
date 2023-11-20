/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabed <mabed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 23:15:21 by mabed             #+#    #+#             */
/*   Updated: 2023/10/20 16:03:37 by mabed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	del_link(t_list *lst)
{
	if (lst == NULL)
		return ;
	if (lst->prev != NULL)
		lst->prev->next = lst->next;
	else
		lst->data->first = lst->next;
	if (lst->next != NULL)
		lst->next->prev = lst->prev;
	else
		lst->data->last = lst->prev;
	free(lst->content);
	free(lst);
}


char	*c_to_str(char c)
{
	char	*str;

	str = malloc(sizeof(char) * 2);
	if (!str)
		return (NULL);
	str[0] = c;
	str[1] = '\0';
	return (str);
}


t_list	*ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	last = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return (NULL);
	}
	if (lst == NULL || new == NULL)
		return (NULL);
	while (last->next != NULL)
		last = last->next;
	last->next = new;
	new->prev = last;
	return (new);
}


t_list	*ft_lstnew(t_data *data, char content, int i)
{
	t_list	*element;
	(void) content;
	element = malloc(sizeof(t_list));
	if (!element)
		return (NULL);
	element->content = c_to_str(content);
	element->next = NULL;
	element->prev = NULL;
	element->token = get_token(element->content);
	element->data = data;
	element->indice = i;
	return (element);
}

void	creat_list(char *str, t_data *data)
{
	int		i;
	int		j;
	 t_list	*list;
	// t_list *head = data->first;
	
	j = 0;
	i = 0;
	if (!str)
		return ;
	data->first = ft_lstnew(data, str[i], j);
	// head = data->first;
	list = data->first;
	while (str[++i] != '\0')
		data->last = ft_lstadd_back(&list, ft_lstnew(data, str[i], ++j));


	// while (head)
	// {
	// 	printf("content = %s\n", head->content);
	// 	head = head->next;
	// }
	// data->first = head;
}