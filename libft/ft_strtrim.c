/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabed <mabed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 19:41:29 by mabed             #+#    #+#             */
/*   Updated: 2022/11/18 21:39:50 by mabed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s2;
	int		i;
	int		j;

	i = 0;
	j = ft_strlen(s1);
	if (!s1 || !set)
		return (NULL);
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	while (j > 0 && ft_strchr(set, s1[j]))
		j--;
	if ((j - i) < 0)
		return (ft_strdup(""));
	s2 = ft_substr(s1, i, (j - i) + 1);
	return (s2);
}

// int main()
// {
// 	printf("%s\n", ft_strtrim("     ws   salut wesh mec      ", " ws"));
// 	return 0;
// }
