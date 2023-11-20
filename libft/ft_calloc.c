/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabed <mabed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:49:22 by mabed             #+#    #+#             */
/*   Updated: 2022/11/22 23:50:31 by mabed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	char	*strc;

	if (num > MAXSIZE || size > MAXSIZE)
		return (NULL);
	strc = malloc(size * num);
	if (!strc)
		return (NULL);
	ft_bzero(strc, num * size);
	return (strc);
}
