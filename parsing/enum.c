/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabed <mabed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 14:11:36 by mabed             #+#    #+#             */
/*   Updated: 2023/11/06 15:13:05 by mabed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// const struct {
// 	char	trigger;
// 	t_token	token;
// } match[] = {
// {'$', DOLLAR},
// };

// t_token get_token(char *str){
// 	int i = 0;
// 	while (match[i].trigger != '\0'){
// 		if (str[0] == match[i].trigger)
// 			return match[i].token;
// 		i++;
// 	}
// 	return ALPHANUMERIC;
// }

t_tokens	get_token(char *str)
{
	if (str[0] == '$')
		return (DOLLAR);
	else if (str[0] == '|')
		return (PIPE);
	else if (str[0] == '<')
		return (REDIRECTION_IN);
	else if (str[0] == '>')
		return (REDIRECTION_OUT);
	else if (str[0] == '?')
		return (INTERRO);
	else if (str[0] == '\'')
		return (SIMPLE_QUOTE);
	else if (str[0] == '\"')
		return (DOUBLE_QUOTE);
	else if (str[0] == ' ' || str[0] == '\t')
		return (SPACES);
	else
		return (ALPHANUMERIC);
}

// void	tokens_distrib(t_list *list)
// {
// 	t_list	*tmp;

// 	tmp = list;
// 	while (tmp->next != NULL)
// 	{
// 		tmp->token = get_token(tmp->content);
// 		tmp = tmp->next;
// 	}
// }

char	*ft_strjoin_free(char const *s1, char const *s2)
{
	char	*str;
	int		j;
	int		i;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[k] = s1[i];
		i++;
		k++;
	}
	while (s2[j])
	{
		str[k] = s2[j];
		j++;
		k++;
	}
	str[k] = '\0';
	free((char*)s1);
	return str;
	//return (free((char *)s1), free((char *)s2), str);
}


void	join_link(t_data *data)
{
	t_list	*tmp;
	t_list	*tmp2;

	tmp = data->first;
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
					data->last = tmp;
				free(tmp2);
				tmp2 = NULL;
			}
			else
					tmp = tmp->next;
		}
	}
}

t_tokens	get_token2(char *str)
{
	if (str[0] == ' ' || str[0] == '\t')
		return (SPACES);
	else
		return (ALPHANUMERIC);
}

void	get_token3(t_list **list)
{
	t_list	*tmp;

	tmp = *list;
	while (tmp && tmp->next != NULL)
	{
		if (tmp->token == REDIRECTION_IN && strlen(tmp->content) == 1)
			tmp->token = FILE_IN;
		else if (tmp->token == REDIRECTION_OUT && strlen(tmp->content) == 1)
			tmp->token = FILE_OUT;
		else if (tmp->token == REDIRECTION_OUT && strlen(tmp->content) == 2)
			tmp->token = FILE_OUT_SUR;
		else if (tmp->token == REDIRECTION_IN && strlen(tmp->content) == 2)
			tmp->token = HERE_DOC;
		tmp = tmp->next;
	}
}

void	get_token4(t_list **list)
{
	t_list	*tmp;

	tmp = *list;
	while (tmp && tmp->next != NULL)
	{
		if (tmp->next)
		{
			if (tmp->token == FILE_IN && tmp->next->token == ALPHANUMERIC)
				tmp->next->token = OPEN_FILE;
			else if (tmp->token == FILE_OUT && tmp->next->token == ALPHANUMERIC)
				tmp->next->token = EXIT_FILE;
			else if (tmp->token == FILE_OUT_SUR && tmp->next->token == ALPHANUMERIC)
				tmp->next->token = EXIT_FILE_RET;
			else if (tmp->token == HERE_DOC && tmp->next->token == ALPHANUMERIC)
				tmp->next->token = LIMITOR;
		}
		tmp = tmp->next;
	}
}

void	get_token5(t_list **list)
{
	t_list	*tmp;

	tmp = *list;
	while (tmp && tmp->next != NULL)
	{
		if (tmp->next->next && tmp->next->token == SPACES)
		{
			if (tmp->token == FILE_IN && tmp->next->next->token == ALPHANUMERIC)
				tmp->next->next->token = OPEN_FILE;
			else if (tmp->token == FILE_OUT &&  tmp->next->next->token == ALPHANUMERIC)
				tmp->next->next->token = EXIT_FILE;
			else if (tmp->token == FILE_OUT_SUR &&  tmp->next->next->token == ALPHANUMERIC)
				tmp->next->next->token = EXIT_FILE_RET;
			else if (tmp->token == HERE_DOC &&  tmp->next->next->token == ALPHANUMERIC)
				tmp->next->next->token = LIMITOR;
		}
		tmp = tmp->next;
	}
	tmp = *list;
	while (tmp != NULL)
	{
		if (tmp->token == ALPHANUMERIC)
			tmp->token = CMD;
		tmp = tmp->next;
	}
}
