/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouzir <cabouzir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 22:24:23 by mabed             #+#    #+#             */
/*   Updated: 2023/11/19 22:35:42 by cabouzir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlensplit(char const *str, char a)
{
	int	i;

	i = 0;
	while (str[i] != a && str[i])
		i++;
	return (i);
}

int	ft_tablen(char const *str1, char a)
{
	int	j;
	int	n;

	j = 0;
	n = 0;
	if (str1[0] != a && str1[0] != '\0')
		n++;
	while (str1[j])
	{
		if (str1[j] == a && str1[j + 1] != a && str1[j + 1] != '\0')
		{
			n++;
		}
		j++;
	}
	return (n);
}

void	free_all(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	**ft_split_under(char const *s, char c, char **tab)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			tab[j] = ft_substr(s, i, ft_strlensplit(&s[i], c));
			if (!tab[j])
			{
				free_all(tab);
				return (NULL);
			}
			i += ft_strlensplit(&s[i], c);
			j++;
		}
		else
			i++;
	}
	tab[j] = NULL;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;

	if (!s || s[0] == '\0')
		return (NULL);
	tab = malloc(sizeof(char *) * (ft_tablen(s, c) + 1));
	if (!tab)
		return (NULL);
	tab = ft_split_under(s, c, tab);
	return (tab);
}

// int	main(void)
// {
//     char const *s4 = "lorem ipsum dolor sit amet, consectetur adipi";
//     char c4 = ' ';
//     int r = 0;
//     char **tib = ft_split(s4, c4);
//     while (r < ft_tablen(s4, c4))
//     {
//         printf("%s\n", tib[r]);
//         r++;
//     }
// 	return (0);
// }