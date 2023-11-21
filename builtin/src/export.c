/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouzir <cabouzir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:53:04 by mpeulet           #+#    #+#             */
/*   Updated: 2023/11/13 05:39:53 by cabouzir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	parse_export(char *new_export_var)
{
	int		i;
	char	**new_var;

	if (new_export_var[0] == '=')
		return (1);
	new_var = ft_split(new_export_var, '=');
	i = -1;
	if (!new_var[0] || ft_strlen(new_var[0]) >= 50)
		return (free_tab1(new_var), 1);
	if (!ft_strcmp(new_var[0], "$?"))
		return (free_tab1(new_var), 0);
	if (ft_isalpha(new_var[0][0]) == 0 && new_var[0][0] != '_')
	{
		// if (ft_isdigit(new_var[0][0]))
		return (free_tab1(new_var), 1);
	}
	while (new_var[0][++i])
	{
		if (!ft_isalpha(new_var[0][i]) && new_var[0][i] != '_'
			&& !ft_isdigit(new_var[0][i]))
			return (free_tab1(new_var), 1);
	}
	return (free_tab1(new_var), 0);
}

			int	add_to_env(char ***env, char *cmd, t_env **envi)
			{
				int		i;
				int		size;
				char	**env_tmp;

				i = 0;
				size = 0;
				while ((*env)[size])
					size++;
				env_tmp = ft_calloc(sizeof(char *), size + 2);
				if (!env_tmp)
					return (0);
				while (i < size)
				{
					env_tmp[i] = (*env)[i];
					i++;
				}
				env_tmp[size] = ft_strdup(cmd);
				ft_envadd_back(envi, ft_envnew(cmd));
				if (!env_tmp[size])
					return (free_tab1(env_tmp), 0);
				env_tmp[size + 1] = 0;
				free_tab1(*env);
				*env = env_tmp;
				return (1);
			}

			int	update_env(char ***env, char *cmd, t_env **envi)
			{
				int		i;
				char	**var;

				var = ft_split(cmd, '=');
				i = 0;
				while ((*env)[i])
				{
					if (!ft_strncmp((*env)[i], var[0], ft_strlen(var[0])))
					{
						if (!ft_strchr(cmd, '='))
							return (free_tab1(var), 0);
						free((*env)[i]);
						(*env)[i] = ft_strdup(cmd);
						update_lst_env(cmd, envi, var);
						if (!(*env)[i])
							return (free_tab1(var), 0);
						return (free_tab1(var), 0);
					}
					i++;
				}
				free_tab1(var);
				return (add_to_env(env, cmd, envi));
			}


char **	add_to_env_tmp(char **env, char *cmd, t_env **envi)
{
	int		i;
	int		size;
	char	**env_tmp;

	i = 0;
	size = 0;
	while ((env)[size])
		size++;
	env_tmp = ft_calloc(sizeof(char *), size + 2);
	if (!env_tmp)
		return (0);
	while (i < size)
	{
		env_tmp[i] = ft_strdup((env)[i]);
		i++;
	}
	env_tmp[size] = ft_strdup(cmd);
	ft_envadd_back(envi, ft_envnew(cmd));
	if (!env_tmp[size])
	{
		free_tab1(env_tmp);
		return NULL;
	}
	env_tmp[size + 1] = 0;
	// free_tab1(env);
	// *env = env_tmp;
	return (env_tmp);
}



char **	update_env_tmp(char **env, char *cmd, t_env **envi)
{
	int		i;
	char	**var;

	var = ft_split(cmd, '=');
	i = 0;
	while ((env)[i])
	{
		if (!ft_strncmp((env)[i], var[0], ft_strlen(var[0])))
		{
			if (!ft_strchr(cmd, '='))
			{
				free_tab1(var);
				return env;
			}
			free((env)[i]);
			(env)[i] = ft_strdup(cmd);
			update_lst_env(cmd, envi, var);
			if (!(*env)[i])
			{
				free_tab1(var);
				return env;
			}

			free_tab1(var);
			return env;

		}
		i++;
	}
	free_tab1(var);
	return (add_to_env_tmp(env, cmd, envi));
}

int	export(char **cmd, t_data *data)
{
	int	i;
	char **tmp;
	i = 1;

	if (!cmd[1])
		return (export_noargs(data->envi), 1);
	while (cmd[i])
	{
		if (parse_export(cmd[i]))
		{
			ft_printf_fd(2, ERR_EXP_PARSE, cmd[i]);
			exit(1); //rajout retour 1
			i++;
			continue ;
		}
		tmp = update_env_tmp(data->envi, cmd[i], &data->env_list);
		free_tab1(data->envi);
		data->envi = tmp;
		i++;
	}
	return (0);
}

void	update_lst_env(char *cmd, t_env **env, char **var)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->content, var[0], ft_strlen(var[0])))
		{
			free(tmp->content);
			tmp->content = ft_strdup(cmd);
		}
		tmp = tmp->next;
	}
}
