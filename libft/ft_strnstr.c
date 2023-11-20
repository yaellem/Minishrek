/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabed <mabed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:28:40 by mabed             #+#    #+#             */
/*   Updated: 2022/12/01 21:22:05 by mabed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (s2[0] == '\0')
		return ((char *)s1);
	while (s1[i])
	{
		while (s1[i + j] == s2[j] && (i + j) < n && s2[j])
		{
			j++;
		}
		if (!s2[j])
			return ((char *)&s1[i]);
		j = 0;
		i++;
	}
	return (0);
}

/*#include <stdio.h>

int main(void)
{
    printf("%s", ft_strnstr("lorem ipsum dolor sit amet", "ipsum", 15));
}*/
