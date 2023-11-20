/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabed <mabed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:55:44 by mabed             #+#    #+#             */
/*   Updated: 2022/11/22 13:54:18 by mabed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*cast;

	cast = (unsigned char *)b;
	while (len--)
	{
		*cast = c;
		cast++;
	}
	return (b);
}
/*int	main()
{
    char str[10] = "okmany";
    //ft_memset(str + 2, 48, 2);
    memset(str, 48, 2);
    printf("%s\n", str);
    //memset(str, 48, 2);
}*/