/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabed <mabed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 00:04:38 by mabed             #+#    #+#             */
/*   Updated: 2023/10/16 16:34:57 by mabed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// liste = le maillont entre les double cotes

char	*replace_dollar_alpha(t_list *lst)
{
	int		i;
	char	*str;

	i = 0;
	while (lst->content[i])
	{
		if (lst->content[i] == '$' && (ft_isalpha(lst->content[i + 1])
				== 1 || lst->content[i + 1] == '_'))
		{
			i++;
			str = get_path_var(lst->data->env_list, lst->content, i);
			if (str == NULL)
				return (replace_alpha_null(lst, i));
			else
				return (replace_alpha_env(lst, str, i));
		}
		i++;
	}
	return (lst->content);
}

char	*replace_dollar_digit(t_list *lst)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = malloc(sizeof(char) * (ft_strlen(lst->content) - 1));
	while (lst->content[i])
	{
		if (lst->content[i] == '$' && ft_isdigit(lst->content[i + 1]) == 1)
			i = i + 2;
		str[j] = lst->content[i];
		i++;
		j++;
	}
	str[j] = '\0';
	free (lst->content);
	return (str);
}

char	*replace_dollar_return_code(t_list *lst)
{
	int		i;
	int		j;
	int		k;
	char	*str;
	char	*tmp;

	i = -1;
	j = -1;
	k = -1;
	tmp = ft_itoa(lst->data->exit_code);
	str = malloc(sizeof(char) * (ft_strlen(lst->content) + ft_strlen(tmp) - 1));
	while (lst->content[++i])
	{
		if (lst->content[i] == '$' && lst->content[i + 1] == '?')
		{
			i = i + 2;
			while (tmp[++k])
				str[++j] = tmp[k];
		}
		str[++j] = lst->content[i];
	}
	str[++j] = '\0';
	free (tmp);
	free (lst->content);
	return (str);
}

// fonction qui va compter le nombre de caractere avant le = pour les env
int	var_env_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

// fonction qui va compter le nombre de caractere apres le $ jusqu'a un
// espace ou un caractere special
int	var_dollar_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (ft_isalnum(str[i]) == 1 || str[i] == '_'))
		i++;
	return (i);
}
