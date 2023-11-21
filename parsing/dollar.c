/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouzir <cabouzir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:53:17 by mabed             #+#    #+#             */
/*   Updated: 2023/11/21 16:19:00 by cabouzir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	replace_dollar(t_data *data)
{
	t_list	*lst;
	t_list	*tmp;
	char	*str;

	lst = data->first;
	while (lst)
	{
		if (lst->indice == -1)
		{
			tmp = lst->next;
			del_link(lst);
			lst = tmp;
		}
		else if (lst->token == DOLLAR)
		{
			if (lst->next && (lst->next->token == ALPHANUMERIC || lst->next->token == INTERRO))
			{
				if (ft_isalnum(lst->next->content[0]) == 1 || lst->next->content[0] == '_' || lst->next->content[0] == '?')
				{
					tmp = lst->next;
					del_link(lst);
					lst = tmp;
					if (ft_isalpha(lst->content[0]) == 1 || lst->content[0] == '_')
					{
						str = get_path_var(lst->data->env_list, lst->content, 0);
						if (str == NULL)
							lst->content = (replace_alpha_null2(lst));
						else
						{
							lst->content = (replace_alpha_env2(lst, str));
							// printf("lst->content = %s\n", lst->content);
							integration(&lst);
						}
					}
					else if (lst->content[0] == '?')
					{
						lst->content = replace_dollar_return_code2(lst);
						lst->token = ALPHANUMERIC;
					}
					else if (ft_isdigit(lst->content[0]) == 1)
						lst->content = replace_dollar_digit2(lst);
				}
				else
					lst->token = ALPHANUMERIC;
			}
			else
			lst->token = ALPHANUMERIC;
		}
		if (lst)
			lst = lst->next;
	}
}

char	*replace_dollar_alpha2(t_list *lst)
{
	char	*str;

	str = get_path_var(lst->data->env_list, lst->content, 0);
	if (str == NULL)
		return (replace_alpha_null(lst, 0));
	else
		return (replace_alpha_env(lst, str, 0));
}

char	*replace_dollar_digit2(t_list *lst)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = malloc(sizeof(char) * ft_strlen(lst->content));
	if (ft_isdigit(lst->content[i]) == 1)
			i = i + 1;
	while (lst->content[i])
	{
		str[j] = lst->content[i];
		i++;
		j++;
	}
	str[j] = '\0';
	free (lst->content);
	return (str);
}

char	*replace_dollar_return_code2(t_list *lst)
{
	int		i;
	int		j;
	int		k;
	char	*str;
	char	*tmp;

	i = 0;
	j = 0;
	k = 0;
	tmp = ft_itoa(lst->data->exit_code);
	puts(tmp);
	str = malloc(sizeof(char) * (ft_strlen(lst->content) + ft_strlen(tmp)));
	while (lst->content[i])
	{
		if (lst->content[i] == '?')
		{
			i = i + 1;
			while (tmp[k])
				str[j++] = tmp[k++];
			j--;
		}
		str[j++] = lst->content[i];
		if (lst->content[i])
			i++;
	}
	str[j] = '\0';
	printf("str = %s\n", str);
	free (tmp);
	free (lst->content);
	return (str);
}

void	integration(t_list **lst)
{
	t_list	*first;
	t_list	*last;

	first = NULL;
	last = NULL;
	creat_list2((*lst)->content, (*lst)->data, &first, &last);
	join_link2(&first, &last);
	if ((*lst)->prev == NULL)
		(*lst)->data->first = first;
	else
	{
		(*lst)->prev->next = first;
		first->prev = (*lst)->prev;
	}
	if ((*lst)->next == NULL)
		(*lst)->data->last = last;
	else
	{
		(*lst)->next->prev = last;
		last->next = (*lst)->next;
	}
	free((*lst));
	*lst = last;
}
