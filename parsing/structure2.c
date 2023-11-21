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
	free(str);	
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
				tmp->content = ft_strjoin_bis(tmp->content, tmp->next->content);
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
	int 	nb_cmd;
	char	***tab;
	t_list	*head;
	
	nb_cmd = 1;
	head = data->first;
	while (head != NULL)
	{
		if (head->token == PIPE)
			nb_cmd++;
		head = head->next;
	}
	data->nb_cmd = nb_cmd;
	if ((tab = malloc(sizeof(char **) * (nb_cmd + 1))) == NULL)
		return (NULL);
	ft_bzero((void*)tab, sizeof(char **) * (nb_cmd + 1));
	tab = sub_tab_cmd(data->first, tab);
	return (tab);
}


char 	***sub_tab_cmd(t_list *user_input_first, char ***tab)
{
	int	n_cmd;
	int i;
	int	j;

	i = 0;
	j = 0;
	while (user_input_first)
	{
		n_cmd = nb_cmd(user_input_first);
		if (!(tab[i] = malloc(sizeof(char *) * (n_cmd + 1))))
			return (free_tab(tab), NULL);
		while (user_input_first != NULL && user_input_first->token != PIPE)
		{
			if (user_input_first->token == CMD && user_input_first->content[0] != '\0')
			{
				tab[i][j] = ft_strdup(user_input_first->content);
				if (!tab[i][j])
					return (free_tab2(tab), NULL);
				j++;
			}
			user_input_first = user_input_first->next;
		}
		tab[i][j] = NULL;
		if (user_input_first)
			user_input_first = user_input_first->next;
		i++;
		j = 0;

	}
	return (tab);
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
	tab = NULL;
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
