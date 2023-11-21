/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouzir <cabouzir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 15:22:21 by mpeulet           #+#    #+#             */
/*   Updated: 2023/11/21 16:12:46 by cabouzir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	default_config(void)
{
	struct sigaction	sa;

	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = sigint_handler_default;
	if (sigaction(SIGINT, &sa, 0))
		return (ft_printf_fd(2, ERR_SIGACTION), 1);
	sa.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sa, 0))
		return (ft_printf_fd(2, ERR_SIGACTION), 1);
	return (0);
}

int	heredoc_config(void)
{
	struct sigaction	sa;

	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = sig_handler_heredoc;
	if (sigaction(SIGINT, &sa, 0))
		return (ft_printf_fd(2, ERR_SIGACTION), 1);
	sa.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sa, 0))
		return (ft_printf_fd(2, ERR_SIGACTION), 1);
	return (0);
}

int	child_config(void)
{
	struct sigaction	sa;

	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SIG_DFL;
	if (sigaction(SIGINT, &sa, 0))
		return (ft_printf_fd(2, ERR_SIGACTION), 1);
	if (sigaction(SIGQUIT, &sa, 0))
		return (ft_printf_fd(2, ERR_SIGACTION), 1);
	return (0);
}

int	parent_config(void)
{
	struct sigaction	sa;

	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = sig_handler_parent;
	if (sigaction(SIGINT, &sa, 0))
		return (ft_printf_fd(2, ERR_SIGACTION), 1);
	sa.sa_handler = sig_handler_parent;
	if (sigaction(SIGQUIT, &sa, 0))
		return (ft_printf_fd(2, ERR_SIGACTION), 1);
	return (0);
}

int	config_signals(int config)
{
	struct sigaction	sa;

	memset(&sa, 0, sizeof(sa));
	if (config == DEFAULT_SIG)
		default_config();
	else if (config == HEREDOC_SIG)
		heredoc_config();
	else if (config == CHILD_SIG)
		child_config();
	else if (config == PARENT_SIG)
		parent_config();
	return (0);
}

void	antislash(int sig)
{
	if (sig == SIGQUIT)
		exit(131);
	if (sig == SIGINT)
		exit(130);
}

void	ctrlc(int sig)
{
	t_data *data;

	data = (t_data *)starton();
	// data = (t_data *)g_data_signal_exit[1];
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		// data->cat = 1;
		data->exit_code = 130;
	}
}

void    ctrlc_2(int sig)
{
    if (sig == SIGINT)
    {
        printf("\n");
    }
}

void	ctrlc_child(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		exit(0);
	}
}

// Might be usefull but commented to test
t_data	*starton(void)
{
	 static t_data	data = {0};

	return (&data);
}

// t_data *starton(void)
// {
// 	t_data *data = malloc(sizeof(t_data));
// 	ft_memset(data, 0, sizeof(t_data));
// 	return data;
// }

/*int	config_signals(int config)
{
	struct sigaction	sa;

	memset(&sa, 0, sizeof(sa));
	if (config == DEFAULT_SIG)
	{
		sa.sa_handler = sigint_handler_default;
		if (sigaction(SIGINT, &sa, 0))
			return (ft_printf_fd(2, ERR_SIGACTION), 1);
		sa.sa_handler = SIG_IGN;
		if (sigaction(SIGQUIT, &sa, 0))
			return (ft_printf_fd(2, ERR_SIGACTION), 1);
	}
	else if (config == HEREDOC_SIG)
	{
		sa.sa_handler = sigint_handler_heredoc;
		if (sigaction(SIGINT, &sa, 0))
			return (ft_printf_fd(2, ERR_SIGACTION), 1);
		sa.sa_handler = SIG_IGN;
		if (sigaction(SIGQUIT, &sa, 0))
			return (ft_printf_fd(2, ERR_SIGACTION), 1);
	}
	else if (config == CHILD_SIG)
	{
		sa.sa_handler = SIG_DFL;
		if (sigaction(SIGINT, &sa, 0))
			return (ft_printf_fd(2, ERR_SIGACTION), 1);
		if (sigaction(SIGQUIT, &sa, 0))
			return (ft_printf_fd(2, ERR_SIGACTION), 1);
	}
	else if (config == PARENT_SIG)
	{
		sa.sa_handler = sig_handler_parent;
		if (sigaction(SIGINT, &sa, 0))
			return (ft_printf_fd(2, ERR_SIGACTION), 1);
		sa.sa_handler = sig_handler_parent;
		if (sigaction(SIGQUIT, &sa, 0))
			return (ft_printf_fd(2, ERR_SIGACTION), 1);
	}
	return (0);
}*/
