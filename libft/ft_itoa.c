/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabed <mabed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:56:06 by mabed             #+#    #+#             */
/*   Updated: 2022/11/22 23:52:51 by mabed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strnblen(int m)
{
	int	nb;
	int	j;

	j = 0;
	if (m < 0)
		nb = -m;
	else
		nb = m;
	while (nb > 0)
	{
		nb = nb / 10;
		j++;
	}
	return (j);
}

char	*ft_neg(int l)
{
	int		i;
	char	*strnb1;

	i = ft_strnblen(l);
	if (l == 0)
		i = 1;
	strnb1 = malloc(sizeof(char) * i + 1);
	if (!strnb1)
		return (0);
	strnb1[i] = '\0';
	i--;
	while (i >= 0)
	{
		strnb1[i] = (l % 10) + 48;
		l = l / 10;
		i--;
	}
	return (strnb1);
}

char	*ft_itoa(int n)
{
	char	*strnb;
	int		i;

	i = ft_strnblen(n);
	if (n >= 0)
		strnb = ft_neg(n);
	else
	{
		if (n == -2147483648)
			return (ft_strdup("-2147483648"));
		strnb = malloc(sizeof(char) * i + 2);
		if (!strnb)
			return (0);
		n = -n;
		strnb[i + 1] = '\0';
		while (i >= 0)
		{
			strnb[i] = (n % 10) + 48;
			n = n / 10;
			i--;
		}
		strnb[0] = 45;
	}
	return (strnb);
}
