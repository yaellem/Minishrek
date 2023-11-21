/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouzir <cabouzir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:52:15 by mpeulet           #+#    #+#             */
/*   Updated: 2023/11/21 17:27:47 by cabouzir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/minishell.h"

int	contains_equal(char *s)
{
	while (*s)
	{
		if (*s == '=')
			return (1);
		s++;
	}
	return (0);
}

void	env_builtin(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		ft_printf_fd(1, env[i]);
		ft_printf_fd(1, "\n");
		contains_equal(env[i]);
	}
}
