/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_noargs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouzir <cabouzir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:23:40 by mpeulet           #+#    #+#             */
/*   Updated: 2023/11/13 05:49:50 by cabouzir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	sort_index(char **tab, int *index, int size)
{
	int	i;
	int	j;
	int	min_index;

	i = 0;
	while (i < size - 1)
	{
		min_index = i;
		j = i + 1;
		while (j < size)
		{
			if (ft_strcmp(tab[index[j]], tab[index[min_index]]) < 0)
				min_index = j;
			j++;
		}
		ft_swap(&index[i], &index[min_index]);
		i++;
	}
}

void	print_export(char **tab, int *index, int size)
{
	int		i;
	char	*sub;
	char	**split;

	i = -1;
	while (++i < size)
	{
		split = ft_split(tab[index[i]], '=');
		sub = ft_strchr(tab[index[i]], '=');
		if (!sub)
		{
			printf("export %s\n", split[0]);
			free_tab1(split);
			continue ;
		}
		if (sub[1] == '"')
			sub = "\"";
		printf("export %s=\"%s\"\n", split[0], sub + 1);
		free_tab1(split);
	}
}

void	export_noargs(char **env)
{
	int	i;
	int	size;
	int	*index;

	i = 0;
	while (env[i])
		i++;
	size = i;
	index = ft_calloc(sizeof(int), size);
	if (!index)
		return ;
	i = -1;
	while (++i < size)
		index[i] = i;
	sort_index(env, index, size);
	print_export(env, index, size);
	free(index);
}

void	export2(char **cmd, t_data *data)
{
	int	i;

	i = 1;
	if (cmd[1])
	{
		while (cmd[i])
		{
			if (parse_export(cmd[i]))
			{
				i++;
				continue ;
			}
			update_env(&data->envi, cmd[i], &data->env_list);
			i++;
		}
	}
}

void	ft_swap(int *a, int *b)
{
	int	x;

	x = 0;
	x = *a;
	a = b;
	*b = x;
}
