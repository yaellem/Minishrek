/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpeulet <mpeulet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 11:11:49 by mabed             #+#    #+#             */
/*   Updated: 2023/11/20 15:43:02 by mpeulet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void child_process(t_data *data, char ***cmds, int i, t_list **tmp)
// {
// 	redirect(data, tmp);
// 	data->exec->cmds = cmds[i];
// 	if (ft_verif_built(data->exec->cmds, data) == -42)
// 		exit(1);
// 	data->exec->cmdpath = access_check(data->exec->path, data->exec->cmds[0]);
// 	if (data->exec->cmdpath != NULL)
// 	{
// 		execve(data->exec->cmdpath, data->exec->cmds, data->exec->path);
// 		free_all_data(data, 1, 3);
// 	}
// 	free_all_data(data, 1, 4);
// }

void	loop_cmd(t_data *data)
{
	int		i;
	t_list	*tmp;
	int ex;
	
	tmp = data->first;
	data->exec->prev = -1;
	i = 0;/*+ data->here_doc*/
	// signal(SIGINT, &ctrlc);
	signal(SIGINT, ctrlc_2);
	printf("START OF FUNC nb cmd = %d\n", data->nb_cmd);
	if (data->nb_cmd == 1)
	{
		data->exec->j = i;
		data->exec->cmds = data->tb_cmd[i];
		ex = ft_verif_built(data->exec->cmds, data);
		printf("IN COMMAND 1 EX VERIF BUILTIN = %d\n", ex);
		if(ex == -42)
			return;
		if(ex == 1)
			return;
		// data->exec->cmdpath = access_check(data->exec->path, data->exec->cmds[0]);
	}
	// data->exec->cmdpath = access_check(data->exec->path, data->exec->cmds[0]);
	while ( i < data->nb_cmd)
	{
		data->exec->j = i;
		if (pipe(data->exec->fd) == -1)
			free_all_data(data, 1, i);
		data->exec->pids[i] = fork();
		if (data->exec->pids[i] == -1)
			free_all_data(data, 1, i);
		if (data->exec->pids[i] == 0)
		{
			printf("I will enter chid process 2 now\n");
			// config_signals(CHILD_SIG);
			child_process_2(data, data->tb_cmd, i, &tmp);
		}
		else
		{
			// config_signals(PARENT_SIG);
			signal(SIGQUIT, ctrlc_2);
			// if (data->nb_cmd == 1)
			// 	ft_verif_built2(data->tb_cmd[i], data);
			close(data->exec->fd[1]);
			if (data->exec->prev != -1)
				close(data->exec->prev);
			// close_fd(&data->exec->fd[1]);
			// close_fd(&data->exec->prev);
			data->exec->prev = data->exec->fd[0];
			// free_data(data);

			
		}
		i++;
	}
	// signal(SIGINT, &ctrlc);
	i = -1;
	while (++i < data->nb_cmd)
	{
		waitpid(data->exec->pids[i], &data->exit_code, 0);
		if (WIFEXITED(data->exit_code))
			data->exit_code = WEXITSTATUS(data->exit_code);
		if (WIFSIGNALED(data->exit_code))
		{
			data->exit_code = WTERMSIG(data->exit_code);
			// if (data->cat == 1)
			// 	data->exit_code += 128;
		}
		if (data->exit_code == 131)
			ft_printf_fd(2, "Quit (core dumped)\n");
	}

	// free_tab1(data->exec->path);
	// free(data->exec->pids);
	// free(data->exec);

	// free(data->tb_cmd);
	// config_signals(PARENT_SIG);
}

// void exec_cmd(t_data *data)
// {
// 	data->exec->pids[0] = fork();
// 	if (data->exec->pids[0] == -1)
// 		free_all_data(data, 1, 0);
// 	if (data->exec->pids[0] == 0)
// 		child_process_2(data, data->tb_cmd, 0);
// 	else
// 		ft_verif_built3(data->tb_cmd[0], data);
// 	waitpid(data->exec->pids[0], NULL, 0);
// 	// waitpid(pid, NULL, 0);
// }

void	child_process_2(t_data *data, char ***cmds, int i, t_list **tmp)
{
	int	j;
	int ex;

	j = 0;
	ex = 0;

	data->n = data->n + 1;
	// dprintf(2, "data->n : %d\n", data->n);
	signal(SIGINT, &antislash);
	signal(SIGQUIT, &antislash);
	while ((*tmp) && j < i)
	{
		if ((*tmp)->token == PIPE)
			j++;
		(*tmp) = (*tmp)->next;
	}
	redirect(data);
	redirect2(data, *tmp);
	data->exec->cmds = cmds[i];

	// if (ft_strcmp(data->exec->cmds[0], "export") == 0)
	// {
	// 	int ret = export(data->exec->cmds, data);
	// 	if (ret == 0)
	// 	{
	// 		free_tab2(data->tb_cmd);
	// 		data->tb_cmd = NULL;
	// 		free(data->exec->pids);
	// 		data->exec->pids = NULL;
	// 				free_tab1(data->exec->path);
	// 				data->exec->path = NULL;
	// 				free(data->exec);
	// 				data->exec = NULL;
	// 		free_list(data->first);
	// 		free_list_env(data->env_list);
	// 		free_tab2(data->tb_cmd);
	// 		// free_tab1(data->envi);
	// 		data->envi = NULL;
	// 		// free(data->exec->pids);
	// 		// free_tab1(data->exec->path);
	// 		free(data->exec);
	// 		data->exec = NULL;

	// 		while (i < data->nb_here)
	// 		{
	// 			free(data->here[i].delim);
	// 			data->here[i].delim = NULL;
	// 			i++;
	// 		}
	// 		free(data->here);
	// 		data->here = NULL;
	// 		free(data);
	// 		data = NULL;
	// 	}
	// 	else {
	// 		free_tab2(data->tb_cmd);
	// 		data->tb_cmd = NULL;
	// 		free(data->exec->pids);
	// 		data->exec->pids = NULL;
	// 		free_tab1(data->exec->path);
	// 		data->exec->path = NULL;
	// 		free(data->exec);
	// 		data->exec = NULL;
	// 		free_data(data);
	// 	}
	// 	exit(0);
	// }
	ex = ft_verif_built(data->exec->cmds, data);
	printf("EX VERIF BUILTIN = %d\n", ex);
	if(ex == -42)
	{
		free_tab2(data->tb_cmd);
		data->tb_cmd = NULL;
		free(data->exec->pids);
		data->exec->pids = NULL;
		free_tab1(data->exec->path);
				data->exec->path = NULL;
				free(data->exec);
				data->exec = NULL;
		free_data(data);
		data = NULL;
		exit(0);
	}
	if(ex == 1)
	{
		free_tab2(data->tb_cmd);
		data->tb_cmd = NULL;
		free(data->exec->pids);
		data->exec->pids = NULL;
		free_tab1(data->exec->path);
		data->exec->path = NULL;
		free(data->exec);
		data->exec = NULL;
		free_data(data);
		data = NULL;
		exit(1);
	}
	// if(is_builtin(data->tb_cmd[0]) == 1)
	data->exec->cmdpath = access_check(data->exec->path, data->exec->cmds[0]);
	if (data->exec->cmdpath != NULL)
	{

		execve(data->exec->cmdpath, data->exec->cmds, data->envi);
		ft_putchar_fd(' ', 2);
		ft_putendl_fd(strerror(errno), 2);
		// free_all_data(data, 1, 3);
		// printf("-----------------> \n");
	}
							free_tab2(data->tb_cmd);
				data->tb_cmd = NULL;
				free(data->exec->pids);
				data->exec->pids = NULL;
				free_tab1(data->exec->path);
				data->exec->path = NULL;
				free(data->exec);
				data->exec = NULL;
		free_data(data);
		data = NULL;
	exit(127);
	// free_all_data(data, 1, 4);
}

int	init(t_data *data)
{
	t_exec	*exec;

	exec = malloc(sizeof(t_exec) * 1);
	if (!exec)
	{
		perror("Erreur d'allocation de mémoire");
		exit(1);
	}
	exec->path = get_paths_from_environment(get_path_var1(data->envi));
	if (exec->path == NULL)
	{
		return (data->exit_code = 0, 0);
	}
	exec->j = 0;
	exec->pids = ft_calloc(sizeof(int), data->nb_cmd + 1);
	if (exec->pids == NULL)
	{
		perror("Erreur d'allocation de mémoire");
		free_data(data);
		// free_tab1(data->exec->path);
		// free(exec);
		exit(1); /*----->free tout ce qui a etai maloc*/
	}
	data->exec = exec;
	return(1);
}

// int	main(int ac, char **av, char **env)
// {
// 	static t_data	data = {.prev = -1, 0};

// 	init(&data, ac, av, env);
// 	loop_cmd(&data, av);
// free_all_data(&data, 0, 4);
// }
