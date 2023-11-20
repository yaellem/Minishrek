/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabed <mabed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:28:13 by mabed             #+#    #+#             */
/*   Updated: 2023/10/06 00:51:54 by mabed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	syntax_error(t_data *data)
{
	t_list	*tmp;

	tmp = data->first;
	while (tmp != NULL)
	{
		if (verif_pipe(tmp) == 1)
			return (data->exit_code = 2, 2);
		if (verif_spaces_chevron(tmp) == 1)
			return (data->exit_code = 2, 2);
		if (tmp->token == REDIRECTION_IN && ft_strlen(tmp->content) == 3)
			return (data->exit_code = 2, printf("minishell: syntax error near unexpected token `<'\n"), 2);
		else if (tmp->token == REDIRECTION_IN && ft_strlen(tmp->content) > 3)
			return (data->exit_code = 2, printf("minishell: syntax error near unexpected token `<<'\n"), 2);
		else if (tmp->token == REDIRECTION_IN && ft_strlen(tmp->content) < 3 && (tmp->next == NULL || (tmp->next->token == SPACES && tmp->next->next == NULL)))
			return (data->exit_code = 2, printf("minishell: syntax error near unexpected token `newline'\n"), 2);
		if (tmp->token == REDIRECTION_OUT && ft_strlen(tmp->content) == 3)
			return (data->exit_code = 2, printf("minishell: syntax error near unexpected token `>'\n"), 2);
		else if (tmp->token == REDIRECTION_OUT && ft_strlen(tmp->content) > 3)
			return (data->exit_code = 2, printf("minishell: syntax error near unexpected token `>>'\n"), 2);
		else if (tmp->token == REDIRECTION_OUT && ft_strlen(tmp->content) < 3 && (tmp->next == NULL || (tmp->next->token == SPACES && tmp->next->next == NULL)))
			return (data->exit_code = 2, printf("minishell: syntax error near unexpected token `newline'\n"), 2);
		if (verif_chev_next_chev(tmp) == 1)
			return (data->exit_code = 2, 2);
		tmp = tmp->next;
	}
	return (0);
}

int	verif_spaces_chevron(t_list *tmp)
{
	if ((tmp->token == REDIRECTION_IN || tmp->token == REDIRECTION_OUT) && tmp->next != NULL && tmp->next->next != NULL && tmp->next->token == SPACES && tmp->next->next->token == REDIRECTION_IN)
	{
		if (ft_strlen(tmp->content) <= 4)
			return (printf("minishell: syntax error near unexpected token `<'\n"), 1);
		else if (ft_strlen(tmp->content) == 5)
			return (printf("minishell: syntax error near unexpected token `<<'\n"), 1);
		else if (ft_strlen(tmp->content) > 5)
			return (printf("minishell: syntax error near unexpected token `<<<'\n"), 1);
	}
	if ((tmp->token == REDIRECTION_IN || tmp->token == REDIRECTION_OUT) && tmp->next != NULL && tmp->next->next != NULL && tmp->next->token == SPACES && tmp->next->next->token == REDIRECTION_OUT)
	{
		if (ft_strlen(tmp->content) <= 4)
			return (printf("minishell: syntax error near unexpected token `>'\n"), 1);
		else if (ft_strlen(tmp->content) == 5)
			return (printf("minishell: syntax error near unexpected token `>>'\n"), 1);
		else if (ft_strlen(tmp->content) > 5)
			return (printf("minishell: syntax error near unexpected token `>>>'\n"), 1);
	}
	return (0);
}

int	verif_chev_next_chev(t_list *tmp)
{
	if (tmp->token == REDIRECTION_IN)
	{
		if (tmp->next->token == REDIRECTION_OUT && ft_strlen(tmp->next->content) == 1)
			return (printf("minishell: syntax error near unexpected token `>'\n"), 1);
		else if (tmp->next->token == REDIRECTION_OUT && ft_strlen(tmp->next->content) > 1)
			return (printf("minishell: syntax error near unexpected token `>>'\n"), 1);
	}
	else if (tmp->token == REDIRECTION_OUT)
	{
		if (tmp->next->token == REDIRECTION_IN && ft_strlen(tmp->next->content) == 1)
			return (printf("minishell: syntax error near unexpected token `<'\n"), 1);
		else if (tmp->next->token == REDIRECTION_IN && ft_strlen(tmp->next->content) > 1)
			return (printf("minishell: syntax error near unexpected token `<<'\n"), 1);
	}
	return (0);
}

int	verif_pipe(t_list *tmp)
{
	if(tmp->token == PIPE && (tmp->prev == NULL || (tmp->prev->token == SPACES && tmp->prev->prev == NULL)))
		return (printf("minishell: syntax error near unexpected token `|'\n"), 1);
	else if((tmp->token ==  PIPE) && ((tmp->prev->token == REDIRECTION_IN || tmp->prev->token == REDIRECTION_OUT) || ((tmp->prev->token == SPACES) && (tmp->prev->prev->token == REDIRECTION_IN || tmp->prev->prev->token == REDIRECTION_OUT))))
		return (printf("minishell: syntax error near unexpected token `|'\n"), 1);
	else if (tmp->token == PIPE && ft_strlen(tmp->content) > 1)
			return (printf("minishell: syntax error near unexpected token `|'\n"), 1);
	else if(tmp->token == PIPE && (tmp->next == NULL || (tmp->next->token == SPACES && tmp->next->next == NULL)))
		return (printf("minishell: syntax error near unexpected token `|'\n"), 1);
	else if(tmp->token == PIPE && tmp->next != NULL && tmp->next->token == SPACES && tmp->next->next->token == PIPE)
		return (printf("minishell: syntax error near unexpected token `|'\n"), 1);
	else
		return (0);
}

//verifier qu'il n'y a pas de spaces entre les chevrons

// if (tmp->token == PIPE && tmp->next->token == REDIRECTION_IN)
// 	return (1);
// if (tmp->token == PIPE && tmp->next->token == REDIRECTION_OUT)
// 	return (1);
// if (tmp->token == REDIRECTION_IN && tmp->next->token == PIPE)
// 	return (1);
// if (tmp->token == REDIRECTION_OUT && tmp->next->token == PIPE)
// 	return (1);

