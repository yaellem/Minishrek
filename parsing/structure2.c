/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouzir <cabouzir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 23:15:21 by mabed             #+#    #+#             */
/*   Updated: 2023/11/18 22:37:13 by cabouzir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*ft_lstnew2(t_data *data, char content, int i)
{
	t_list	*element;

	element = malloc(sizeof(t_list));
	if (!element)
		return (NULL);
	element->content = c_to_str(content);
	element->next = NULL;
	element->prev = NULL;
	element->token = get_token2(element->content);
	element->data = data;
	element->indice = i;
	return (element);
}

void	creat_list2(char *str, t_data *dbl_list, t_list **first, t_list **last)
{
	int		i;
	int		j;
	t_list	*list;

	j = 0;
	i = 0;
	if (!str)
		return ;
	*first = ft_lstnew2(dbl_list, str[i], j);
	list = *first;
	while (str[++i] != '\0')
		*last = ft_lstadd_back(&list, ft_lstnew2(dbl_list, str[i], ++j));
}

void	join_link2(t_list **first, t_list **last)
{
	t_list	*tmp;
	t_list	*tmp2;

	tmp = *first;
	if (tmp != NULL)
	{
		while (tmp->next != NULL)
		{
			if (tmp->token == tmp->next->token && tmp->token != SIMPLE_QUOTE
				&& tmp->token != DOUBLE_QUOTE)
			{
				tmp->content = ft_strjoin(tmp->content, tmp->next->content);
				tmp2 = tmp->next;
				tmp->next = tmp->next->next;
				if (tmp2->next != NULL)
					tmp2->next->prev = tmp;
				else
					*last = tmp;
				free(tmp2);
			}
			else
					tmp = tmp->next;
		}
	}
}

char	***tab_cmd(t_data *data)
{
	int		i;
	// int		j;
	// int		k;
	char	***tab;
	t_list	*tmp;

	i = 1;
	tmp = data->first;
	while (tmp != NULL)
	{
		if (tmp->token == PIPE)
			i++;
		tmp = tmp->next;
	}
	data->nb_cmd = i;
	tab = malloc(sizeof(char **) * (i + 1));
	if (!tab)
		return (NULL);
	tmp = data->first;
	i = 0;
	while (tmp != NULL)
	{
		if (sub_tab_cmd(&tmp, &tab, &i) == -1)
			return (NULL);
	}
	tab[i] = NULL;
	return (tab);
}


int 	sub_tab_cmd(t_list **tmp_datafirst, char ****tab, int *i)
{
	int	k;
	int	j;

	j = 0;
	k = nb_cmd(*tmp_datafirst);
	(*tab)[*i] = malloc(sizeof(char *) * (k + 1));
	if (!(*tab)[*i])
		return (free_tab(*tab), -1);
	while (*tmp_datafirst != NULL && (*tmp_datafirst)->token != PIPE)
	{
		if ((*tmp_datafirst)->token == CMD && (*tmp_datafirst)->content[0] != '\0')
		{
			(*tab)[*i][j] = ft_strdup((*tmp_datafirst)->content);
			if (!(*tab)[*i][j])
				return (free_tab2(*tab), -1);
			//printf("addr of tab[i][j] = %p\n", (*tab)[*i][j]);
			j++;
		}
		(*tmp_datafirst) = (*tmp_datafirst)->next;
	}
	(*tab)[*i][j] = NULL;
	if ((*tmp_datafirst) != NULL)
		*tmp_datafirst = (*tmp_datafirst)->next;
	(*i)++;
	return (0);
}
void 	free_tab2(char ***tab)
{
	int	i;
	int	j;

	i = 0;
	if (tab == NULL)
		return;
	while (tab[i] != NULL)				
	{
		j = 0;
		while (tab[i][j] != NULL)
		{
			free(tab[i][j]);
			tab[i][j] = NULL;
			j++;
		}
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
}

void 	free_tab(char ***tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}

int	nb_cmd(t_list *lst)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = lst;
	while (tmp && (tmp->token != PIPE))
	{
		if (tmp->token == CMD && tmp->content[0] != '\0')
			i++;
		tmp = tmp->next;
	}
	return (i);
}
