/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabed <mabed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 22:21:55 by mabed             #+#    #+#             */
/*   Updated: 2023/10/20 15:40:11 by mabed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*replace_alpha_null2(t_list *lst)
{
	int		j;
	int		k;
	char	*str;

	j = var_dollar_len(lst->content);
	k = 0;
	str = malloc(sizeof(char) * (ft_strlen(lst->content)
				- var_dollar_len(lst->content) + 1));
	while (lst->content[j])
		str[k++] = lst->content[j++];
	str[k] = '\0';
	free (lst->content);
	return (str);
}

char	*replace_alpha_env2(t_list *lst, char *str)
{
	int		j;
	int		k;
	int		l;
	char	*tmp;

	j = var_dollar_len(lst->content);
	k = 0;
	l = var_env_len(str) + 1;
	tmp = malloc(sizeof(char) * (ft_strlen(lst->content)
				- var_dollar_len(lst->content) + ft_strlen(str + l) + 1));
	while (str[l])
	{
		tmp[k] = str[l];
		k++;
		l++;
	}
	while (lst->content[j])
	{
		tmp[k] = lst->content[j];
		j++;
		k++;
	}
	tmp[k] = '\0';
	free (lst->content);
	return (tmp);
}
