/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouzir <cabouzir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 19:14:24 by mabed             #+#    #+#             */
/*   Updated: 2023/11/21 15:20:36 by cabouzir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_path_var1(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
			return (env[i]);
	}
	return("");
}

char	**get_paths_from_environment(char *path)
{
	return (ft_split(path + 5, ':'));
}

char	*access_check(char **env, char *cmd)
{
	int		j;
	char	*path_cmd;
	char	*tmp;

	j = 0;
	if (!cmd)
		return (ft_putstr_fd("command not found\n", 2), NULL);
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	while (env[j])
	{
		tmp = ft_strjoin("/", cmd);
		path_cmd = ft_strjoin(env[j], tmp);
		free(tmp);
		if (access(path_cmd, F_OK) == 0)
			return (path_cmd);
		j++;
		free(path_cmd);
	}
	write(2, cmd, strlen(cmd));
	ft_putstr_fd(": command not found", 2);
	write(2, "\n", 1);
	return (NULL);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (-1);
	while ((s1[i] && s2[i]) && (s1[i] == s2[i]))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_strncmp(const char *s1, const char *s2, const size_t n)
{
	size_t	i;
	int		j;

	i = n;
	j = 0;
	while (i && s1[j] && s2[j])
	{
		if (s1[j] != s2[j])
			return (s1[j] - s2[j]);
		j++;
		i--;
	}
	return (0);
}
