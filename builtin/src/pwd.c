/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouzir <cabouzir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:50:45 by mpeulet           #+#    #+#             */
/*   Updated: 2023/11/13 05:38:09 by cabouzir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	pwd(void)
{
	static char	buf[MAX_PWD] = {0};

	if (!getcwd(buf, MAX_PWD))
		return (ft_putendl_fd(ERR_PWD, 2), 1);
	else
		ft_putendl_fd(buf, 1);
	return (0);
}
