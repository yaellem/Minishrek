/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabed <mabed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:44:52 by mabed             #+#    #+#             */
/*   Updated: 2022/11/18 02:08:34 by mabed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*a;
	unsigned char	*b;
	size_t			i;

	a = (unsigned char *)dest;
	b = (unsigned char *)src;
	i = 0;
	if (dest > src)
	{
		while (n > 0)
		{
			a[n - 1] = b[n - 1];
			n--;
		}
	}
	else
	{	
		while (i < n)
		{
			a[i] = b[i];
			i++;
		}
	}
	return (dest);
}
