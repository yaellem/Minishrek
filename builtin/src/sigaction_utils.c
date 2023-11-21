/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigaction_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouzir <cabouzir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:22:56 by mpeulet           #+#    #+#             */
/*   Updated: 2023/11/21 16:19:34 by cabouzir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	sigint_handler_default(int signum)
{
	(void)signum;
	// g_data_signal_exit[0] = 130;
	ft_putchar_fd(10, 2);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sig_handler_parent(int signum)
{
	if (signum == SIGINT)
		ft_putchar_fd(10, 2);
	else if (signum == SIGQUIT)
		ft_putstr_fd(CORE_DUMP, 2);
}

void	sig_handler_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		// g_data_signal_exit[0] = 130;
		ft_putchar_fd(10, 2);
		close(0);
		close(1);
	}
}
