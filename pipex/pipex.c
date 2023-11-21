/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouzir <cabouzir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 11:11:49 by mabed             #+#    #+#             */
/*   Updated: 2023/11/21 15:53:43 by cabouzir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	free_data_in_subprocess(t_data *data)
{
		free_tab2(data->tb_cmd);
		data->tb_cmd = NULL;
		if (data->exec){
			free(data->exec->pids);
			data->exec->pids = NULL;
			//free(data->exec->cmdpath);
			//data->exec->cmdpath = NULL;
			free_tab1(data->exec->path);
			data->exec->path = NULL;	
		}
		free(data->exec);
		data->exec = NULL;
		free_data(data);
}

void	free_data_in_parent(t_data *data)
{
		free_tab2(data->tb_cmd);
		data->tb_cmd = NULL;
		if (data->exec){
			free(data->exec->pids);
			data->exec->pids = NULL;
		//	free(data->exec->cmdpath);
		//	data->exec->cmdpath = NULL;
			free_tab1(data->exec->path);
			data->exec->path = NULL;	
		}
		free(data->exec);
		data->exec = NULL;
}

void	loop_cmd(t_data *data)
{
	int		i;
	int 	ret;
	t_list	*tmp;
	
	tmp = data->first;
	data->exec->prev = -1;
	i = 0;/*+ data->here_doc*/
	// signal(SIGINT, &ctrlc);
	signal(SIGINT, ctrlc_2);
	if (data->nb_cmd == 1)
	{
		data->exec->j = i;
		data->exec->cmds = data->tb_cmd[i];
		ret = ft_verif_built(data->exec->cmds, data);
		if(ret != NO_BUILTIN) 
		{
			data->exit_code = 0;
			free_data_in_parent(data);
			return;
		}
	}

	while (i < data->nb_cmd)
	{
		data->exec->cmds = data->tb_cmd[i];
		
		if ((data->exec->cmdpath = access_check(data->exec->path, data->exec->cmds[0])) == NULL)
		{
			i++;
			free(data->exec->cmdpath);
			data->exec->cmdpath = NULL;
			data->exit_code = 130;
			continue;
		}	
		data->exec->j = i;
		if (data->nb_cmd > 1 && pipe(data->exec->fd) == -1)
			free_all_data(data, 1, i);
		data->exec->pids[i] = fork();
		if (data->exec->pids[i] == -1)
			free_all_data(data, 1, i);
		if (data->exec->pids[i] == 0)
			child_process_2(data, data->tb_cmd, i, &tmp);
		else
		{
			signal(SIGQUIT, ctrlc_2);
			// close(data->exec->fd[1]);
			if (data->exec->prev != -1)
				close(data->exec->prev);
			data->exec->prev = data->exec->fd[0];
		}
		free(data->exec->cmdpath);
		data->exec->cmdpath = NULL;
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
		}
		if (data->exit_code == 131)
			ft_printf_fd(2, "Quit (core dumped)\n");
	}
	free_data_in_parent(data);
}


void	child_process_2(t_data *data, char ***cmds, int i, t_list **tmp)
{
	int	j;
	int ex;

	j = 0;
	ex = 0;

	free(data->exec->cmdpath);
	data->exec->cmdpath = NULL;
	data->n = data->n + 1;
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

	ex = ft_verif_built(data->exec->cmds, data);
	if(ex == -42)
	{
		free_data_in_subprocess(data);
		exit(0);
	}
	if(ex == 1)
	{
		free_data_in_subprocess(data);
		exit(1);
	}
	data->exec->cmdpath = access_check(data->exec->path, data->exec->cmds[0]);
	if (data->exec->cmdpath != NULL)
	{

		execve(data->exec->cmdpath, data->exec->cmds, data->envi);
		ft_putchar_fd(' ', 2);
		ft_putendl_fd(strerror(errno), 2);
	}
	free(data->exec->cmdpath);
	data->exec->cmdpath = NULL;
	free_data_in_subprocess(data);
	exit(127);
}

int	input_lexer(t_data *data)
{
	t_exec	*exec;

	exec = malloc(sizeof(t_exec) * 1);
	ft_bzero((void *)exec, sizeof(t_exec) * 1);
	if (!exec)
	{
		perror("Erreur d'allocation de mémoire");
		exit(1);
	}
	exec->path = get_paths_from_environment(get_path_var1(data->envi));
	if (exec->path == NULL)
	{
		free(exec);
		return (data->exit_code = 0, 0);
	}
	exec->j = 0;
	exec->pids = ft_calloc(sizeof(int), data->nb_cmd + 1);
	if (exec->pids == NULL)
	{
		perror("Erreur d'allocation de mémoire");
		free_data(data);
		exit(1); /*----->free tout ce qui a etai maloc*/
	}
	data->exec = exec;
	return(1);
}

