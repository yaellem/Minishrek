/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_quote2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabed <mabed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:06:44 by mabed             #+#    #+#             */
/*   Updated: 2023/10/19 16:40:35 by mabed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// i et l indice du caractere apres le dollar
char	*get_path_var(t_env *env, char *tmp, int i)
{
	t_env	*tmp_env;

	tmp_env = env;
	if (!env)
		exit(1);
	while (tmp_env != NULL)
	{
		if (var_env_len(tmp_env->content) == var_dollar_len(tmp + i))
		{
			if (ft_strncmp(tmp_env->content, tmp + i,
					var_env_len(tmp_env->content)) == 0)
				return (tmp_env->content);
		}
		tmp_env = tmp_env->next;
	}
	return (NULL);
}

char	*replace_alpha_null(t_list *lst, int i)
{
	int		j;
	int		k;
	char	*str;

	j = 0;
	k = 0;
	str = malloc(sizeof(char) * (ft_strlen(lst->content)
				- var_dollar_len(lst->content + i)));
	while (lst->content[j])
	{
		if (j == (i - 1))
			j = j + var_dollar_len(lst->content + i) + 1;
		if (lst->content[j])
			str[k++] = lst->content[j++];
	}
	str[k] = '\0';
	free (lst->content);
	return (str);
}

char	*replace_alpha_env(t_list *lst, char *str, int i)
{
	int		j;
	int		k;
	int		l;
	char	*tmp;

	j = 0;
	k = 0;
	l = var_env_len(str) + 1;
	tmp = malloc(sizeof(char) * (ft_strlen(lst->content)
				- var_dollar_len(lst->content + i) + ft_strlen(str + l)));
	while (lst->content[j])
	{
		if (j == (i - 1))
		{
			j = j + var_dollar_len(lst->content + i) + 1;
			while (str[l])
			{
				tmp[k] = str[l];
				k++;
				l++;
			}
		}
		if (lst->content[j])
		{
			tmp[k] = lst->content[j];
			j++;
			k++;
		}
	}
	tmp[k] = '\0';
	free (lst->content);
	return (tmp);
}
