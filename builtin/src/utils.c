/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 10:12:36 by mpeulet           #+#    #+#             */
/*   Updated: 2023/11/20 11:03:45 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// t_list	*env_to_lst(char **env)
// {
// 	t_list	*head;
// 	t_list	*new;
// 	char	*env_copy;
// 	int		i;

// 	i = -1;
// 	head = 0;
// 	while (env[++i])
// 	{
// 		env_copy = ft_strdup(env[i]);
// 		if (!env_copy)
// 		{
// 			ft_lstclear(&head, &free);
// 			return (NULL);
// 		}
// 		new = ft_lstnew(env_copy);
// 		if (!new)
// 		{
// 			free(env_copy);
// 			ft_lstclear(&head, &free);
// 			return (NULL);
// 		}
// 		ft_lstadd_back(&head, new);
// 	}
// 	return (head);
// }

char	*ft_get_env(char *var_name, char **env)
{
	int	i;
	int	len;

	i = -1;
	len = ft_strlen(var_name);
	while (env[++i])
	{
		if (!ft_strncmp(env[i], var_name, len) && env[i][len] == '=')
			return (env[i] + len + 1);
	}
	return (NULL);
}

// char	**copy_tab(char **src)
// {
// 	int		i;
// 	int		size;
// 	char	**copy;

// 	if (!src)
// 		return (0);
// 	size = 0;
// 	while (src[size])
// 		size++;
// 	copy = ft_calloc(sizeof(char *), size + 1);
// 	if (!copy)
// 		return (0);
// 	i = 0;
// 	while (i < size)
// 	{
// 		copy[i] = ft_strdup(src[i]);
// 		if (!copy[i])
// 			return (free_tab(copy), NULL);
// 		i++;
// 	}
// 	copy[size] = 0;
// 	return (copy);
// }

// void	init_environ(void)
// {
// 	int		i = 0;
// 	char	**tmp;

// 	tmp = copy_tab(__environ);
// 	i = 0;
// 	while (__environ[i])
// 	{
// 		__environ[i] = 0;
// 		i++;
// 	}
// 	__environ = 0;
// 	__environ = tmp;
// 	tmp = 0;
// }

// char	**lst_to_chartab(t_list *env)
// {
// 	int     i;
// 	char    **tab;
// 	t_list  *tmp;

// 	i = 0;
// 	tmp = env;
// 	tab = ft_calloc(ft_lstsize(env) + 1, sizeof(char *));
// 	if (!tab)
// 		return (NULL);
// 	while (tmp)
// 	{
// 		tab[i] = ft_strdup(tmp->content);
// 		if (!tab[i])
// 			return (free_tab(tab), NULL);
// 		tmp = tmp->next;
// 		i++;
// 	}
// 	tab[i] = 0;
// 	return (tab);
// }

char	*trim_path(char *path)
{
	int	i;
	int	len;

	len = ft_strlen(path);
	if (len > 0 && path[len - 1] == '/')
		len --;
	i = len - 1;
	while (i >= 0)
	{
		if (path[i] == '/')
		{
			if (i == 0)
				path[i + 1] = 0;
			else
				path[i] = 0;
			break ;
		}
		i--;
	}
	return (path);
}

int	ft_strlen_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

// t_list	*return_link_by_str(t_list *env, char *str)
// {
// 	t_list	*tmp;

// 	tmp = env;
// 	while (tmp)
// 	{
// 		if (!ft_strncmp(tmp->content, str, ft_strlen(str)))
// 			return (tmp);
// 		tmp = tmp->next;
// 	}
// 	return (NULL);
// }

// void	update_env_lst(t_list **env, char *cmd)
// {
// 	while (*env)
// 	{
// 		if (!ft_strncmp((*env)->content, cmd, ft_strlen(cmd)))
// 		{
// 			free((*env)->content);
// 			(*env)->content = ft_strdup(cmd);
// 			break ;
// 		}
// 		env = &(*env)->next;
// 	}
// }

/*int	ft_chdir(char *s, t_list **env)
{
	char	*gtcwd;

	if (!ft_strcmp(s, ".."))
	{
		gtcwd = getcwd(NULL, 0);
		if (!chdir(".."))
		{
			update_env_lst(env, "OLDPWD=", gtcwd);
			free(gtcwd);
			gtcwd = getcwd(NULL, 0);
			update_env_lst(env, "PWD=", gtcwd);
			free(gtcwd);
			return (0);
		}
	}
	else if (!chdir(s))
	{
		gtcwd = getcwd(NULL, 0);
		update_env_lst(env, "OLDPWD=", return_link_by_str(*env, "PWD=")->content);
		update_env_lst(env, "PWD=", gtcwd);
		free(gtcwd);
		return (0);
	}
	return (1);
}*/

/*int	cd(char **cmd, t_list **env)
{
	int		i;
	t_list	*tmp;

	i = -1;
	while (cmd[++i])
		if (i >= 2)
			return (ft_printf_fd(2, ERR_CD_MANY), 1);
	if (!cmd[1] || !ft_strcmp(cmd[1], "~"))
	{
		tmp = return_link_by_str(*env, "HOME=");
		if (!tmp)
			return (ft_printf_fd(2, ERR_CD_HOME, cmd[1]), 1);
		if (chdir(ft_memchr(tmp->content, '/', ft_strlen(tmp->content))))
			return (ft_printf_fd(2, ERR_CD,
					ft_memchr(tmp->content, '=', ft_strlen(tmp->content)), 1));
	}
	else if (!ft_strcmp(cmd[1], "-"))
	{
		tmp = return_link_by_str(*env, "OLDPWD=");
		if (!tmp)
			return (ft_printf_fd(2, ERR_CD_OPWD, cmd[1]), 1);
		if (ft_chdir(ft_memchr(tmp->content, '/',
					ft_strlen(tmp->content)), env))
			return (ft_printf_fd(2, ERR_CD, cmd[1]), 1);
	}
	else if (ft_chdir(cmd[1], env))
		return (ft_printf_fd(2, ERR_CD, cmd[1]), 1);
	return (0);
}*/

/*int	cd(char **cmd, t_list **env)
{
	(void)env;
	int		i;
	char	*env_var;

	i = -1;
	while (cmd[++i])
		if (i >= 2)
			return (ft_printf_fd(2, ERR_CD_MANY), 1);
	if (!cmd[1] || !ft_strcmp(cmd[1], "~"))
	{
		env_var = getenv("HOME");
		if (!env_var)
			return (ft_printf_fd(2, ERR_CD_HOME, cmd[1]), 1);
		if (chdir(env_var))
			return (ft_printf_fd(2, ERR_CD, env_var, 1));
	}
	else if (!ft_strcmp(cmd[1], "-"))
	{
		env_var = getenv("OLDPWD");
		if (!env_var)
			return (ft_printf_fd(2, ERR_CD_OPWD, cmd[1]), 1);
		if (chdir(env_var))
			return (ft_printf_fd(2, ERR_CD, cmd[1]), 1);
	}
	else if (chdir(cmd[1]))
		return (ft_printf_fd(2, ERR_CD, cmd[1]), 1);
	return (0);
}*/

/*int	cd(char **cmd)
{
	int		i;
	char	*env_var;

	i = -1;
	while (cmd[++i])
		if (i >= 2)
			return (ft_printf_fd(2, ERR_CD_MANY), 1);
	if (!cmd[1] || !ft_strcmp(cmd[1], "~"))
	{
		env_var = getenv("HOME");
		if (!env_var)
			return (ft_printf_fd(2, ERR_CD_HOME, cmd[1]), 1);
		if (chdir(env_var))
			return (ft_printf_fd(2, ERR_CD, env_var, 1));
	}
	else if (!ft_strcmp(cmd[1], "-"))
	{
		env_var = getenv("OLDPWD");
		if (!env_var)
			return (ft_printf_fd(2, ERR_CD_OPWD, cmd[1]), 1);
		if (chdir(env_var))
			return (ft_printf_fd(2, ERR_CD, cmd[1]), 1);
	}
	else if (!ft_strcmp(cmd[1], ".."))
	{
		env_var = trim_path(getcwd(NULL, 0));
		chdir(env_var);
		free(env_var);
	}
	else if (chdir(cmd[1]))
		return (ft_printf_fd(2, ERR_CD, cmd[1]), 1);
	return (0);
}*/
