/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouzir <cabouzir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 00:16:31 by cabouzir          #+#    #+#             */
/*   Updated: 2023/11/19 21:10:38 by cabouzir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	get_len_word(char *str)
// {
// 	int	i;
// 	int	r;

// 	i = 0;
// 	r = 0;
// 	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
// 		i++;
// 	while (str[i] && str[i] != ' ' && str[i] != '\t' && !ft_strchr("><|&",
// 			str[i]))
// 	{
// 		i++;
// 		r++;
// 	}
// 	return (r);
// }

// char	*get_word(char *str)
// {
// 	int		i;
// 	int		r;
// 	char	*new;

// 	new = malloc(get_len_word(str) + 1);
// 	i = 0;
// 	r = 0;
// 	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
// 		i++;
// 	while (str[i] && str[i] != ' ' && str[i] != '\t' && !ft_strchr("><|&",
// 			str[i]))
// 		new[r++] = str[i++];
// 	new[r] = 0;
// 	return (new);
// }

t_here	*here_doc(t_data *data, char *str)
{
	int		i;
	pid_t	pid;

	data->nb_here = count_hd(data->first);
	if (!data->nb_here)
		return (NULL);
	data->here = ft_calloc(sizeof(t_here), data->nb_here);
	ft_getdelims(str, data->here, data);
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
		// config_signals(DEFAULT_SIG);
	}
	// signal(SIGINT, &ctrlc);
	// signal(SIGINT, &ctrlc);
	int stat = 0;
	waitpid(pid, &stat, 0);
	if (WIFEXITED(stat))
	{
		stat = WEXITSTATUS(stat);
		// printf("------------------------> %d\n", stat);
	}
	if (stat == 130)
	{
		data->here_status = 1;
		data->exit_code = 130;
		// printf("------------------------> %d\n", stat);
	}
	// config_signals(DEFAULT_SIG);
	return (NULL);
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
	// {
	// 	if (str[i] == '<')
	// 	{
	// 		i++;
	// 		if (str[i] == '<')
	// 		{
	// 			nb++;
	// 			i++;
	// 		}
	// 	}
	// 	i++;
	// }
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
				// dprintf(2,"fd heredoc %d = %d et %d\n", nb, here[nb].pipe[1], here[nb].pipe[0]);
				nb++;
			}
		}
		i++;
	}
}

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

	data = starton();
	// static t_data	data = {0};
	// printf("data->here-----------> : %p\n", data->here);
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 2);
		i = -1;
		while (++i < data->nb_here)
		{
			// dprintf(2,"CLOSE fd heredoc %d = %d et %d\n", i, data->here[i].pipe[1], data->here[i].pipe[0]);
			close(data->here[i].pipe[1]);
			close(data->here[i].pipe[0]);
			if (data->here[i].delim != NULL)
				ft_free_m((void **)&data->here[i].delim);
		}
		free_data(data);
		// rl_replace_line("", 0);
		// rl_on_new_line();
		// rl_redisplay();
		// free_all(2, 2, &data->str, &data->here, data->path, data->env);
		exit(130);
	}
}


void	child_hd(t_data *data, char *str)
{
	int	i;

	data->n = data->n + 1;
	(void)str;
	// config_signals(HEREDOC_SIG);
	i = -1;
	while (++i < data->nb_here)
		openfileshd(i, data->here);
	free_data(data);
	// ici free TOUT CE QUI A ETE ALLOUEE avant d'avoir appele la fonction heredoc
	exit(1);
}

char	*openfileshd(int index, t_here *here)
{
	char	*s;

	// config_signals(HEREDOC_SIG);
	signal(SIGINT, &exit_hd);
	while (1)
	{
		s = readline("here_doc> ");
		if (!s || !ft_strcmp(s, here[index].delim))
			break ;
		ft_putendl_fd(s, here[index].pipe[1]); 
		// config_signals(HEREDOC_SIG, here[index].pipe[1], here[index].pipe[0]);
		free(s);
	}
	close(here[index].pipe[1]);
	close(here[index].pipe[0]);
	return (NULL);
}

// void    free_heredoc(t_here *here, t_data *data)
// {
//     while(data->nb_here >= 0)
//     {
//         free(here[data->nb_here]->delim);
//         close(here[data->nb_here]->pipe[0]);
//         data->nb_here--;
//     }
// }