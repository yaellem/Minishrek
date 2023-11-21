/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouzir <cabouzir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 00:16:31 by cabouzir          #+#    #+#             */
/*   Updated: 2023/11/21 16:37:16 by cabouzir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_free_m(void **ptr)
{
	if (*ptr)
		free(*ptr);
	*ptr = NULL;
	return (NULL);
}

static void	exit_hd(int sig)
{
	t_data	*data;
	int		i;

	// data = (t_data *)g_data_signal_exit[1];
	data = (t_data *)starton();
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 2);
		i = -1;
		while (++i < data->nb_here)
		{
			close(data->here[i].pipe[1]);
			close(data->here[i].pipe[0]);
		}
		free(data->readlin_return);
		data->readlin_return = NULL;
		free_data((t_data *)data);
		// g_data_signal_exit[1] = 0;
		// g_data_signal_exit[2] = 0;
		exit(130);
	}
}


int 	here_doc(t_data *data, char *str)
{
	int		i;
	pid_t	pid;

	data->nb_here = count_hd(data->first);
	printf("here doc nb = %d\n", data->nb_here);
	data->here = NULL;
	if (!data->nb_here)
		return (TRUE);
	data->here = ft_calloc(sizeof(t_here), data->nb_here);
	ft_getdelims(str, data->here, data);
	// signal(SIGINT, &exit_hd);
	signal(SIGINT, SIG_IGN);
	// config_signals(DEFAULT_SIG);
	pid = fork();
	i = -1;
	if (pid == 0)
		child_hd(data, str);
	else if (pid > 0)
	{
		while (++i < data->nb_here)
			close(data->here[i].pipe[1]);
	}
	int stat = 0;
	waitpid(pid, &stat, 0);
	if (WIFEXITED(stat))
		stat = WEXITSTATUS(stat);
	if (stat == 130)
	{
		data->here_status = 1;
		data->exit_code = 130;
		for (int i = 0; i < data->nb_here; i++)
		{
			free(data->here[i].delim);
			data->here[i].delim = NULL;
			i++;
		}
		free(data->here);
		data->here = NULL;
		free_data_in_parent(data);
		return (FALSE);
	}
	// for (int i = 0; i < data->nb_here; i++)
	// {
	// 	free(data->here[i].delim);
	// 	data->here[i].delim = NULL;
	// 	i++;
	// }
	//free(data->here);
	//data->here = NULL;
	return (TRUE);
}

int	count_hd(t_list *list)
{
	int	nb;
	t_list	*tmp;

	nb = 0;
	tmp = list;
	while (tmp != NULL)
	{
		if (tmp->token == LIMITOR)
			nb++;
		tmp = tmp->next;
	}
	return (nb);
}

void	ft_getdelims(char *str, t_here *here, t_data *data)
{
	int		nb;
	int		i;
	t_list	*tmp;

	i = 0;
	nb = 0;
	tmp = data->first;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'')
				i++;
			i++;
		}
		else if (str[i] == '\"')
		{
			i++;
			while (str[i] != '\"')
				i++;
			i++;
		}
		if (str[i] == '<')
		{
			i++;
			if (str[i] == '<')
			{
				i++;
				here[nb].delim = get_word(&str[i], &tmp);
				pipe(here[nb].pipe);
				nb++;
			}
		}
		i++;
	}
}


void	child_hd(t_data *data, char *str)
{
	int	i;

	data->n = data->n + 1;
	i = -1;
	while (++i < data->nb_here)
		openfileshd(i, data->here);
	printf("Child hd before free data\n");
	free(str);
	for (int i = 0; i < data->nb_here; i++)
		{
			free(data->here[i].delim);
			data->here[i].delim = NULL;
			i++;
		}
		free(data->here);
		data->here = NULL;
	free_data(data);
	printf("IN HERE DOC CHILD\n");
	exit(1);
}

char	*openfileshd(int index, t_here *here)
{
	char	*s;

	signal(SIGINT, &exit_hd);
	while (1)
	{
		s = readline("here_doc> ");
		if (!s || !ft_strcmp(s, here[index].delim))
			break ;
		ft_putendl_fd(s, here[index].pipe[1]); 
		free(s);
	}
	close(here[index].pipe[1]);
	close(here[index].pipe[0]);
	return (NULL);
}
