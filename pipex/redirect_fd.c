/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouzir <cabouzir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:27:00 by mabed             #+#    #+#             */
/*   Updated: 2023/11/19 03:34:32 by cabouzir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_fd(int *fd)
{
	if (*fd == -1)
		return ;
	if (close(*fd) != 0)
	{
		perror("Close");
		// dprintf(2, "errrrrrrrrrrror2\n");
	}
	*fd = -1;
}

void	close_pipes(t_data *data)
{
	if ((data->exec->j) < data->nb_cmd - 1) /*data->len = data->nb_cmd*/
		close_fd(&data->exec->fd[0]);
	close_fd(&data->exec->fd[1]);
}

int	getpipe(t_here *here, t_data *data, char *file)
{
	int i = 0;
	while (i < data->nb_here)
	{
			if (!ft_strcmp(here[i].delim, file))
			return (here[i].pipe[0]);
		i++;
	}
	// dprintf(2, "here_doc_not_found\n");
	return (-1);
}
void	redirect(t_data *data)
{
	if (data->exec->j != 0)
	{
		dup2(data->exec->prev, STDIN_FILENO);
		close(data->exec->prev);
	}
	if (data->exec->j != data->nb_cmd - 1)
		dup2(data->exec->fd[1], STDOUT_FILENO);
	close(data->exec->fd[1]);
	close(data->exec->fd[0]);
	// close_pipes(data);
	// redirect2(data);
}
// si il n y as pas de pipe alor il entre dans aucune des condition et il close les fd des pipes

int	open_file2(int fd, t_list *tmp, t_data *data)
{
	if (tmp->token == EXIT_FILE)
		fd = open(tmp->content, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (tmp->token == EXIT_FILE_RET)
		fd = open(tmp->content, O_WRONLY | O_CREAT | O_APPEND, 0666);
	else if (tmp->token == OPEN_FILE)
		fd = open(tmp->content, O_RDONLY);
	else if (tmp->token == LIMITOR)
		fd = getpipe(data->here, data, tmp->content);
	return (fd);
}

int	redirect2(t_data *data, t_list *tmp1)
{
	t_list	*tmp;
	int		fd;

	fd = -1;
	tmp = tmp1;
	while (tmp != NULL && tmp->token != PIPE)
	{
		// printf("[[[%s]]]]\n", tmp->content);
		if (tmp->token == EXIT_FILE || tmp->token == EXIT_FILE_RET || tmp->token ==  OPEN_FILE || tmp->token == LIMITOR)
		{
			fd = open_file2(fd, tmp, data);
			if (fd == -1)
			{
				perror(tmp->content);
				// dprintf(2, "errrrrrrrrrrror\n");
				exit(1);
			}
			// return (invalid_fd_nofork(data, cmd, tmp->file));
			if (tmp->token == EXIT_FILE || tmp->token == EXIT_FILE_RET)
				dup2(fd, STDOUT_FILENO);
			else
				dup2(fd, STDIN_FILENO);
			close(fd);
		}
		tmp = tmp->next;
	}
	// while (i < data->nb_hd)
	// 	close(data->docs[i].fd[0]);
	return (0);
}
