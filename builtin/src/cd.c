/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouzir <cabouzir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:51:16 by mpeulet           #+#    #+#             */
/*   Updated: 2023/11/13 05:46:52 by cabouzir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	cd_to_many(char **cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
		if (i >= 2)
			return (1);
	return (0);
}

// int	ft_strlen_tab(char **tab)
// {
// 	int	i;

// 	i = 0;
// 	while (tab[i])
// 		i++;
// 	return (i);
// }

// char	**modif_env(char **env, char *new_pwd)
// {
// 	char *str;
// 	char **new_env;
// 	int i;

// 	i = 0;
// 	new_env = malloc(sizeof(char **) * ft_strlen_tab(env) + 1);
// 	while(env[i])
// 	{
// 		if(ft_strncmp(env[i], "PWD=", 4) == 0)
// 		{
// 			str = malloc(sizeof(char *) * (ft_strlen(&env[i][4])));
// 			str = ft_strdup(&env[i][4]);
// 			break ;
// 		}
// 		i++;
// 	}
// 	i = 0;
// 	while(env[i])
// 	{
// 		if(ft_strncmp(env[i], "PWD=", 4) == 0)
// 			new_env[i] = ft_strjoin("PWD=", new_pwd);
// 		else if(ft_strncmp(env[i], "OLDPWD=", 7) == 0)
// 			new_env[i] = ft_strjoin("OLDPWD=", str);
// 		else
// 			new_env[i] = ft_strdup(env[i]);
// 		i++;
// 	}
// 	new_env[i] = NULL;
// 	free(str);
// 	return(new_env);
// }

int	cd_home(char **cmd, char **env, t_data *data)
{
	char	*env_var;

	env_var = ft_get_env("HOME", env);
	if (!env_var)
		return (ft_printf_fd(2, ERR_CD_HOME, cmd[1]), 0);
	if (chdir(env_var) == -1)
		return (ft_printf_fd(2, ERR_CD, env_var, 0));
	else
		modif_env(data, env_var); // modifiction de l'environnement
	return (1);
}

int	cd_minus(char **cmd, char **env, t_data *data)
{
	char	*env_var;

	env_var = ft_get_env("OLDPWD", env);
	if (!env_var)
		return (ft_printf_fd(2, ERR_CD_OPWD, cmd[1]), 0);
	if (chdir(env_var) == -1)
		return (ft_printf_fd(2, ERR_CD, cmd[1]), 0);
	else
		modif_env(data, env_var);
	return (1);
}

int	cd_point_point(t_data *data)
{
	char	*env_var;

	env_var = trim_path(getcwd(NULL, 0));
	if (!env_var)
		return (ft_printf_fd(2, ERR_CD_POINT_ALLOC), 0);
	if (chdir(env_var) == -1)
	{
		free(env_var);
		return (0);
	}
	else
		modif_env(data, env_var);
	free(env_var);
	return (1);
}

int	cd(char **cmd, t_data *data)
{
	if (cd_to_many(cmd))
		return (ft_printf_fd(2, ERR_CD_MANY), 1);
	if (!cmd[1] || !ft_strcmp(cmd[1], "~"))
	{
		if (!cd_home(cmd, data->envi, data))
		{
			return (1);
		}
	}
	else if (!ft_strcmp(cmd[1], "-"))
	{
		if (!cd_minus(cmd, data->envi, data))
			return (1);
	}
	else if (!ft_strcmp(cmd[1], ".."))
	{
		if (cd_point_point(data))
			return (0);
	}
	else if (chdir(cmd[1]) == -1)
		return (ft_printf_fd(2, ERR_CD, cmd[1]), 1);
	else
		modif_env(data, ft_strjoin(ft_strjoin(ft_get_env("PWD", data->envi),
					"/"), cmd[1]));
	return (0);
}

// void	swap_pwd(t_data *data, char *new_pwd)
// {
// 	char	*str;
// 	int		i;

// 	str = ft_get_env("PWD", data->envi);
// 	while (data->env_list != NULL)
// 	{
// 		if (ft_strncmp(data->env_list->content, "PWD=", 4) == 0)
// 			data->env_list->content = ft_strjoin("PWD=", new_pwd);
// 		if (ft_strncmp(data->env_list->content, "OLDPWD=", 7) == 0)
// 			data->env_list->content = ft_strjoin("OLDPWD=", str);
// 		data->env_list = data->env_list->next;
// 	}
// 	i = 0;
// 	while(data->envi[i])
// 	{
// 		if (ft_strncmp(data->envi[i], "PWD=", 4) == 0)
// 			data->envi[i] = ft_strjoin("PWD=", new_pwd);
// 		else if (ft_strncmp(data->envi[i], "OLDPWD=", 7) == 0)
// 			data->envi[i] = ft_strjoin("OLDPWD=", str);
// 		i++;
// 	}
// }