/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 14:44:47 by naessgui          #+#    #+#             */
/*   Updated: 2025/07/12 16:52:14 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	check_redirections(t_token **list)
{
	t_token	*current;

	current = *list;
	if (!current)
		return (false);
	while (current)
	{
		if (current->type == T_RED_IN || current->type == T_RED_OUT
			|| current->type == T_APPEND || current->type == T_HEREDOC)
		{
			if (current->next == NULL)
				return (*list = current, true);
			if (current->next->type != T_WORD
				&& current->next->type != T_D_QUOTE
				&& current->next->type != T_S_QUOTE
				&& current->next->type != T_ENV)
				return (*list = current, true);
		}
		current = current->next;
	}
	return (false);
}

static bool	check_pipe(t_token **list)
{
	t_token	*current;

	current = *list;
	if (current && current->type == T_PIPE)
	{
		*list = current;
		return (true);
	}
	while (current)
	{
		if (current->type == T_PIPE)
		{
			if (current->next == NULL || current->next->type == T_PIPE)
			{
				*list = current;
				return (true);
			}
		}
		current = current->next;
	}
	return (false);
}

bool	check_error1(t_token **list)
{
	t_token	*save;

	save = *list;
	if (check_pipe(list))
	{
		if ((*list)->next && (*list)->next->type == T_PIPE)
			printf("minishell: syntax error near unexpected token `|'\n");
		else if (*list && (*list)->type == T_PIPE && (*list)->next == NULL)
			printf("minishell: syntax error near unexpected token `|'\n");
		else if (*list && (*list)->type == T_PIPE)
			printf("minishell: syntax error near unexpected token `|'\n");
		return (true);
	}
	*list = save;
	if (check_redirections(list))
	{
		if (*list && (*list)->next == NULL)
			printf("minishell: syntax error near unexpected token `newline'\n");
		else if (*list && (*list)->next)
			printf("minishell: syntax error near unexpected token `%s'\n",
				(*list)->next->token);
		return (true);
	}
	return (false);
}
