/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cabouzir <cabouzir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 15:45:56 by mabed             #+#    #+#             */
/*   Updated: 2023/11/19 21:21:48 by cabouzir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	verif_quote(char *line)
// {
// 	int	i;
// 	int	quote;

// 	i = 0;
// 	quote = 0;
// 	while (line[i])
// 	{
// 		if (line[i] == '\'')
// 		{
// 			if (quote == 0)
// 				quote = 2;
// 			else if (quote == 2)
// 				quote = 0;
// 		}
// 		else if (line[i] == '\"')
// 		{
// 			if (quote == 0)
// 				quote = 1;
// 			else if (quote == 1)
// 				quote = 0;
// 		}
// 		i++;
// 	}
// 	if (quote != 0)
// 		return (1);
// 	return (0);
// }

int	verif_quote(char *line, t_data *data)
{
	int	i;
	int	quote;

	i = -1;
	quote = 0;
	while (line[++i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			if (quote == 0 && line[i] == '\'')
				quote = 2;
			else if (quote == 0 && line[i] == '\"')
				quote = 1;
			else if (quote == 2 && line[i] == '\'')
				quote = 0;
			else if (quote == 1 && line[i] == '\"')
				quote = 0;
		}
	}
	if (quote != 0)
	{
		data->exit_code = 2;
		return (printf("minishell: syntax error quote unclosed\n"), 2);
	}
	return (0);
}

void	ft_negative(char *line)
{
	int	i;
	int	quote;

	i = -1;
	quote = 0;
	while (line[++i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			//printf("DEBUG 2: %c %d\n", line[i], i);
			if (quote == 0 && line[i] == '\'')
				quote = 2;
			else if (quote == 0 && line[i] == '\"')
					quote = 1;
			while (line[++i] && ((line[i] != 34 && quote == 1)
					|| (line[i] != 39 && quote == 2)))
			{
				// if (quote == 2 && line[i + 1] == '\'')
				// {
				// 	quote = 0;
				// 	break ;
				// }
				// else if (quote == 1 && line[i + 1] == '\"')
				// {
				// 	quote = 0;
				// 	break ;
				// }
				// if ((quote == 2 && line[i] != '\'') || (quote == 1 && line[i] != '\"'))
				//printf("DEBUG 1: %c %d\n", line[i], i);
				line[i] = line[i] * -1;
			}
			quote = 0;
		}
	}
}

void	ft_positive(t_data *data)
{
	t_list	*tmp;
	int		i;

	tmp = data->first;
	while (tmp != NULL)
	{
		i = 0;
		if (tmp->next != NULL && (tmp->token == SIMPLE_QUOTE || tmp->token == DOUBLE_QUOTE))
		{
			if (tmp->next->token == ALPHANUMERIC)
			{
				tmp = tmp->next;
				while (tmp->content[i])
				{
					if (tmp->content[i] < 0)
						tmp->content[i] = tmp->content[i] * -1;
					i++;
				}
			}
		}
		if (tmp != NULL)
			tmp = tmp->next;
	}
}

void	replace_quote(t_data *data)
{
	t_list	*tmp;
	t_list	*tmp2;
	int		i;

	tmp = data->first;
	while (tmp != NULL)
	{
		i = 0;
		if (tmp && tmp->token == SIMPLE_QUOTE)
		{
			if (tmp->prev != NULL && tmp->prev->token == DOLLAR)
				tmp->prev->indice = -1;
			if (tmp->next && tmp->next->token == ALPHANUMERIC)
			{
				tmp2 = tmp->next;
				del_link(tmp);
				tmp = tmp2;
				del_link(tmp->next);
			}
			else if (tmp->next && tmp->next->token == SIMPLE_QUOTE)
			{
				tmp2 = tmp->next;
				del_link(tmp);
				tmp = tmp2;
				tmp2 = tmp->next;
				del_link(tmp);
				tmp = tmp2;
				i = 1;
			}
		}
		if (tmp && tmp->token == DOUBLE_QUOTE)
		{
			if (tmp->prev != NULL && tmp->prev->token == DOLLAR)
				tmp->prev->indice = -1;
			if (tmp->next && tmp->next->token == ALPHANUMERIC)
			{
				tmp2 = tmp->next;
				del_link(tmp);
				tmp = tmp2;
				replace_dollar_quote(tmp);
				del_link(tmp->next);
			}
			else if (tmp->next && tmp->next->token == DOUBLE_QUOTE)
			{
				tmp2 = tmp->next;
				del_link(tmp);
				tmp = tmp2;
				tmp2 = tmp->next;
				del_link(tmp);
				tmp = tmp2;
				i = 1;
			}
		}
		if (tmp != NULL && i == 0)
			tmp = tmp->next;
	}
	tmp2 = NULL;
}

void	replace_dollar_quote(t_list *lst)
{
	int		i;

	i = 0;
	while (lst->content[i])
	{
		if (lst->content[i] == '$' && (ft_isalnum(lst->content[i + 1]) == 1
				|| lst->content[i + 1] == '_' || lst->content[i + 1] == '?'))
		{
			if (ft_isalpha(lst->content[i + 1]) == 1
				|| lst->content[i + 1] == '_')
				lst->content = replace_dollar_alpha(lst);
			else if (lst->content[i + 1] == '?')
				lst->content = replace_dollar_return_code(lst);
			else if (ft_isdigit(lst->content[i + 1]) == 1)
				lst->content = replace_dollar_digit(lst);
			i = 0;
		}
		else
			i++;
	}
}

// void	del_empty_join_quote(t_data *data)
// {
// 	t_list	*tmp;
// 	t_list	*tmp2;
// 	int		i;

// 	int
// 	tmp = data->first;
// 	while (tmp != NULL)
// 	{
// 		if ((tmp->token == SIMPLE_QUOTE || tmp->token == DOUBLE_QUOTE)))
// 		{
// 			int i = 0;
// 			tmp2 = tmp->next;
// 			del_link(tmp);
// 			tmp = tmp2;
// 			tmp2 = tmp->next;
// 			del_link(tmp);
// 			tmp = tmp2;
// 		}
// 		if (tmp != NULL)
// 			tmp = tmp->next;
// 	}
// 	tmp = data->first;
// 	while (tmp != NULL)
// 	{
// 		printf("%s\n", tmp->content);
// 		printf("token: %u\n", tmp->token);
// 		printf("--------------ici---------------------------\n");
// 		tmp = tmp->next;
// 	}
// }
