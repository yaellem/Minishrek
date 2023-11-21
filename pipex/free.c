/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouzir <cabouzir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 02:28:36 by mabed             #+#    #+#             */
/*   Updated: 2023/11/19 05:32:58 by cabouzir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_tab1(char **tab)
{
	int	i;

	i = 0;
	if (tab == NULL)
		return ;
	while (tab[i])
	{
		free (tab[i]);
		tab[i] = NULL;
		i++;
	}
	free (tab);
	tab = NULL;
}

void	free_all_data(t_data *data, int code, int code2)
{
	// (void)code;
	if (code2 < 4)
	{
		perror(" ");
		// dprintf(2, "errrrrrrrrrrror4\n");
	}
	if (code2 > 0)
	{
		free_tab1(data->exec->path);
	 	data->exec->path = NULL;
	}
	// if (code2 > 1)
	// 	free_tab1(data->exec->cmds);
	if (code2 > 2)
	{
		free(data->exec->pids);
		data->exec->pids = NULL;
	}
	// printf("----------------->%d\n", code);
	
	exit(code);
	// exit(data->exit_code);
}
