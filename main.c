/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouzir <cabouzir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 15:21:00 by mabed             #+#    #+#             */
/*   Updated: 2023/11/21 16:34:47 by cabouzir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	g_status;
uint64_t			g_data_signal_exit[3] = {0, 0, 0};

void	free_list(t_list *lst)
{
	t_list	*tmp;

	while (lst != NULL)
	{
		tmp = lst->next;
		free(lst->content);
		lst->content = NULL;
		free(lst);
		lst = tmp;
	}
}

void	free_list_env(t_env *env)
{
	t_env	*tmp;

	while (env != NULL)
	{
		tmp = env->next;
		free(env->content);
		env->content = NULL;
		free(env);
		env = tmp;
	}
}

int	is_builtin(char **cmds)
{
	if (ft_strcmp(cmds[0], "echo") == 0)
		return (0);
	else if (ft_strcmp(cmds[0], "cd") == 0)
		return (0);
	else if (ft_strcmp(cmds[0], "env") == 0)
		return (0);
	else if (ft_strcmp(cmds[0], "exit") == 0)
		return (0);
	else if (ft_strcmp(cmds[0], "export") == 0)
		return (0);
	else if (ft_strcmp(cmds[0], "pwd") == 0)
		return (0);
	return (1);
}

void	free_data(t_data *data)
{
	int	i;

	i = 0;
	free_list(data->first);
	data->first = NULL;
	free_list_env(data->env_list);
	data->env_list = NULL;
	free_tab2(data->tb_cmd);
	data->tb_cmd = NULL;
	free_tab1(data->envi);
	data->envi = NULL;
	if (data->exec)
	{
		free_tab1(data->exec->path);
		data->exec->path = NULL;
		free(data->exec->pids);
		data->exec->pids = NULL;
	}
	free(data->exec);
	data->exec = NULL;
	while (i < data->nb_here && data->here)
	{
		free(data->here[i].delim);
		data->here[i].delim = NULL;
		i++;
	}
	free(data->here);
	data->here = NULL;
	// free(data);
//	data = NULL;
}

int	main(int ac, char **av, char **env)
{
	char			*line;
	t_data			*data;
	char			*str;
	int				i;

	(void)ac;
	(void)av;
	
	data = starton();
	g_data_signal_exit[1] = (uint64_t)data;
	// ft_memset(data, 0, sizeof(t_data));
	data->env_list = creat_env_lst(env);
	data->envi = env2(data->env_list);
	data->n = 1;
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &ctrlc);
		errno = 0;
		line = readline("minishell$ ");
		data->readlin_return = line;
		if (!line)
			break ;
		if (!*line)
			continue ;
		if (!env[0])
			continue ;
		add_history(line);
		str = ft_strdup(line);
		data->readlin_return = str;
		// g_data_signal_exit[2] = (uint64_t)str; // Used to free in child of here doc
		if (verif_quote(line, data) <= 0)
		{
			ft_negative(line);
			creat_list(line, data);
			join_link(data);
			if (syntax_error(data) == 0)
			{
				ft_positive(data);
				replace_quote(data);
				replace_dollar(data);
				join_link(data);
				get_token3(&data->first);
				get_token4(&data->first);
				get_token5(&data->first);
				data->tb_cmd = tab_cmd(data);
				input_lexer(data);
				if (here_doc(data, str) == TRUE)
				{
					free(str);
					str = NULL;
					if (data->tb_cmd[0] != NULL && data->tb_cmd && data->tb_cmd[0][0] && data->here_status == 0)
						loop_cmd(data);
					data->here_status = 0;
					while (data->here && i < data->nb_here)
					{
						free(data->here[i].delim);
						data->here[i].delim = NULL;
						i++;
					}
					free(data->here);
					data->here = NULL;
				}
			}
		}
		free(str);
		str = NULL;
		free_list(data->first);
		data->first = NULL;
	}
	i = data->exit_code;
	free_data(data);
	return (i);
}
