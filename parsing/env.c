/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:17:35 by mabed             #+#    #+#             */
/*   Updated: 2023/11/20 12:41:32 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*ft_envnew(char *content)
{
	t_env	*element;

	element = malloc(sizeof(t_env));
	if (!element)
		return (NULL);
	element->content = ft_strdup(content);
	element->next = NULL;
	return (element);
}

t_env	*ft_envadd_back(t_env **lst, t_env *new)
{
	t_env	*last;

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
	return (new);
}

t_env	*creat_env_lst(char **content)
{
	int		i;
	t_env	*list;
	t_env	*env;

	i = 0;
	if (!content[0])
		return (NULL);
	env = ft_envnew(content[i]);
	list = env;
	while (content[++i] != NULL)
		env = ft_envadd_back(&list, ft_envnew(content[i]));
	return (list);
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env != NULL)
	{
		tmp = env->next;
		free(env->content);
		free(env);
		env = tmp;
	}
}

char	**env2(t_env *env)
{
	int		i;
	char	**tab;
	t_env	*tmp;

	i = 0;
	if (!env)
		return (NULL);
	tmp = env;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	tab = malloc(sizeof(char *) * (i + 1));
	i = 0;
	tmp = env;
	while (tmp != NULL)
	{
		tab[i] = ft_strdup(tmp->content);
		tmp = tmp->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
