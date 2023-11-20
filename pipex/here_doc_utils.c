/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabed <mabed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 06:05:17 by cabouzir          #+#    #+#             */
/*   Updated: 2023/11/15 13:41:48 by mabed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_len_word(char *str)
{
	int	i;
	int	r;

	i = 0;
	r = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	while (str[i] && str[i] != ' ' && str[i] != '\t' && !ft_strchr("\'\"",
			str[i]))
	{
		i++;
		r++;
	}
	return (r);
}

char	*get_word(char *str, t_list **tmp)
{
	int		i;
	int		r;
	int		j;
	char	*new;

	new = malloc(get_len_word(str) + 1);
	i = 0;
	r = 0;
	j = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t' || ft_strchr("\'\"",
				str[i])))
		i++;
	while (str[i] && str[i] != ' ' && str[i] != '\t' && !ft_strchr("\'\"",
			str[i]))
	{
		while ((*tmp) && (*tmp)->token != LIMITOR)
			(*tmp) = (*tmp)->next;
		// dprintf(2, "tmp->content = %s\n", (*tmp)->content);
		if (str[i] == '$')
		{
			if ((str[i + 1] && str[i + 1] != '\'' && str[i + 1] != '\"') || str[i + 1] == '\0')
			{
				j = 1;
				new[r++] = '$';
				i++;
			}
			else if (str[i + 1] && (str[i + 1] == '\'' || str[i + 1] == '\"'))
				i++;
		}
		if (str[i] != '\'' && str[i] != '\"')
			new[r++] = str[i++];
		else
			i++;
	}
	new[r] = 0;
	if (j == 1)
	{
		free((*tmp)->content);
		(*tmp)->content = ft_strdup(new);
	}
	// dprintf(2, "new = %s\n", new);
	// dprintf(2, "tmp->content = %s\n", (*tmp)->content);
	return (new);
}
