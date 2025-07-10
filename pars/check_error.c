/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 12:03:57 by naessgui          #+#    #+#             */
/*   Updated: 2025/07/10 18:54:56 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdbool.h>

static bool	check_pipe(t_token **list)
{
	t_token	*tmp;

	tmp = *list;
	if (!tmp)
		return (true);
	if (tmp->type == T_PIPE)
	{
		return (true);
	}
	while (tmp)
	{
		if (tmp->type == T_PIPE && tmp->next && tmp->next->type == T_PIPE)
			return (true);
		if (tmp->type == T_PIPE && tmp->next == NULL)
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

static bool	check_redirections(t_token **list)
{
	t_token	*tmp;

	tmp = *list;
	if (!tmp)
		return (true);
	while (tmp)
	{
		if ((tmp->type == T_RED_IN || tmp->type == T_RED_OUT
				|| tmp->type == T_APPEND || tmp->type == T_HEREDOC))
		{
			if (tmp->next == NULL)
				return (true);
			else if (tmp->next->type != T_WORD && tmp->next->type != T_D_QUOTE
				&& tmp->next->type != T_S_QUOTE && tmp->next->type != T_ENV
				&& tmp->next->type != T_SPACE)
				return (true);
		}
		tmp = tmp->next;
	}
	return (false);
}

bool	check_error(t_token **list)
{
	if (check_redirections(list))
	{
		printf("minishell : syntax error near unexpected token=====`newline'\n");
		return (true);
	}
	if (check_pipe(list) == 1)
	{
		printf("minishell : syntax error near unexpected token `|'\n");
		return (true);
	}
	return (false);
}
