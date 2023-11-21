/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouzir <cabouzir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 01:01:28 by mabed             #+#    #+#             */
/*   Updated: 2023/11/19 19:51:24 by cabouzir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	ft_strcmp(char *s1, char *s2)
// {
// 	int	i;

// 	i = 0;
// 	while (s1[i] && s1[i] == s2[i])
// 		i++;
// 	return (s1[i] - s2[i]);
// }

int ft_verif_built(char **cmds, t_data *data)
{
	if (ft_strcmp(cmds[0], "echo") == 0)
		return (echo(cmds), BUILTIN_RET);
	// else if (ft_strcmp(cmds[0], "cd") == 0)
	// 	return (cd(cmds, data), -42);
	else if (ft_strcmp(cmds[0], "cd") == 0)
	{
		if (cd(cmds, data) == 0)
			return (BUILTIN_RET);
		else
			return (1);
		// return (cd(cmds, data), BUILTIN_RET);
	}
	else if (ft_strcmp(cmds[0], "pwd") == 0)
		return (pwd(), BUILTIN_RET);
	else if (ft_strcmp(cmds[0], "export") == 0)
	{
		return (export(cmds, data), BUILTIN_RET);
	}
	else if (ft_strcmp(cmds[0], "unset") == 0)
		return (unset(cmds, &data->envi), BUILTIN_RET);
	else if (ft_strcmp(cmds[0], "env") == 0)
		return (env_builtin(data->envi), BUILTIN_RET);
	else if (ft_strcmp(cmds[0], "exit") == 0)
		return (exit_builtin(cmds, data, 1), BUILTIN_RET);
	else
		return (NO_BUILTIN);
}

void ft_verif_built2(char **cmds, t_data *data)
{
	printf("I VERIFY in buiTLIN 2\n");
	// while ((*tmp) != NULL && (*tmp)->token != PIPE)
	// 	(*tmp) = (*tmp)->next;
	// if (*tmp && (*tmp)->token == PIPE)
	// 	(*tmp) = (*tmp)->next;
	if (ft_strcmp(cmds[0], "cd") == 0)
		cd2(cmds, data);
	else if (ft_strcmp(cmds[0], "export") == 0)
		return (export2(cmds, data));
	else if (ft_strcmp(cmds[0], "exit") == 0)
		exit_builtin(cmds, data, 0);
	else if (ft_strcmp(cmds[0], "unset") == 0)
		unset(cmds, &data->envi);
	// else if (ft_strcmp(cmds[0], "unset") == 0)
	// return(unset(cmds), -42);
	// else if (ft_strcmp(cmds[0], "exit") == 0)
	// 	return(exit(cmds), -42);
	else
		return;
}

// void ft_verif_built3(char **cmds, t_data *data)
// {
// 	if (ft_strcmp(cmds[0], "cd") == 0)
// 		cd2(cmds, data);
// 	else if (ft_strcmp(cmds[0], "export") == 0)
// 		return (export2(cmds, data));
// 	else if (ft_strcmp(cmds[0], "exit") == 0)
// 		exit_builtin(cmds, data);
// 	// else if (ft_strcmp(cmds[0], "unset") == 0)
// 	// return(unset(cmds), -42);
// 	// else if (ft_strcmp(cmds[0], "exit") == 0)
// 	// 	return(exit(cmds), -42);
// 	else
// 		return ;
// }
