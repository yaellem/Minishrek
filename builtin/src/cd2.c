/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouzir <cabouzir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:31:47 by mabed             #+#    #+#             */
/*   Updated: 2023/11/19 20:07:45 by cabouzir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

int	cd_home2(char **cmd, char **env, t_data *data)
{
	char	*env_var;

	(void)cmd;
	env_var = ft_get_env("HOME", env);
	if (!env_var)
		return (0);
	if (chdir(env_var) == -1)
		return (0);
	else
		modif_env(data, env_var);
	return (1);
}

int	cd_minus2(char **cmd, char **env, t_data *data)
{
	char	*env_var;

	(void)cmd;
	env_var = ft_get_env("OLDPWD", env);
	if (!env_var)
		return (0);
	if (chdir(env_var) == -1)
		return (0);
	else
		modif_env(data, env_var);
	return (1);
}

int	cd_point_point2(t_data *data)
{
	char	*env_var;

	env_var = trim_path(getcwd(NULL, 0));
	if (!env_var)
		return (0);
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

int	cd2(char **cmd, t_data *data)
{
	if (cd_to_many(cmd))
		return (1);
	if (!cmd[1] || !ft_strcmp(cmd[1], "~"))
	{
		if (!cd_home2(cmd, data->envi, data))
		{
			return (1);
		}
	}
	else if (!ft_strcmp(cmd[1], "-"))
	{
		if (!cd_minus2(cmd, data->envi, &*data))
			return (1);
	}
	else if (!ft_strcmp(cmd[1], ".."))
	{
		if (cd_point_point2(data))
			return (0);
	}
	else if (chdir(cmd[1]) == -1)
		return (1);
	else
		modif_env(data, ft_strjoin(ft_strjoin(ft_get_env("PWD", data->envi),
					"/"), cmd[1]));
	return (0);
}

// void	modif_env(t_data *data, char *new_pwd)
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
// 	while (data->envi[i])
// 	{
// 		if (ft_strncmp(data->envi[i], "PWD=", 4) == 0)
// 			data->envi[i] = ft_strjoin("PWD=", new_pwd);
// 		else if (ft_strncmp(data->envi[i], "OLDPWD=", 7) == 0)
// 			data->envi[i] = ft_strjoin("OLDPWD=", str);
// 		i++;
// 	}
// }

void    modif_env(t_data *data, char *new_pwd)
{
    char    *str;
    int        i;
    t_env    *tmp;
    char **tmp_env;

    tmp_env = data->envi;
    tmp = data->env_list;
    str = ft_get_env("PWD", data->envi);
    while (tmp != NULL)
    {
        if (ft_strncmp(tmp->content, "PWD=", 4) == 0)
            tmp->content = ft_strjoin("PWD=", new_pwd);
        if (ft_strncmp(tmp->content, "OLDPWD=", 7) == 0)
            tmp->content = ft_strjoin("OLDPWD=", str);
        tmp = tmp->next;
    }
    i = 0;
    while (tmp_env[i])
    {
        if (ft_strncmp(tmp_env[i], "PWD=", 4) == 0)
            tmp_env[i] = ft_strjoin("PWD=", new_pwd);
        else if (ft_strncmp(tmp_env[i], "OLDPWD=", 7) == 0)
            tmp_env[i] = ft_strjoin("OLDPWD=", str);
        i++;
    }
}
