/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:48:55 by naessgui          #+#    #+#             */
/*   Updated: 2025/07/01 12:33:08 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redirection	*add_new(int type, char *file_name)
{
	t_redirection	*node;

	node = malloc(sizeof(t_redirection));
	node->type = type;
	node->file = ft_strdup(file_name);
	node->next = NULL;
	return (node);
}

void	ft_add_back_redi(t_redirection **head, t_redirection *node)
{
	t_redirection	*tmp;

	if (!*head)
	{
		*head = node;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
	node->next = NULL;
}

t_redirection	*get_files(t_token *token)
{
	t_token			*tmp;
	t_redirection	*head;
	t_redirection	*node;
	t_token			*prev;

	tmp = token;
	head = NULL;
	node = NULL;
	prev = tmp;
	tmp = tmp->next;
	while (tmp && tmp->type != T_PIPE)
	{
		if ((prev->type == T_RED_OUT || prev->type == T_APPEND
				|| prev->type == T_RED_IN || prev->type == T_HEREDOC)
			&& (tmp->type == T_WORD || tmp->type == T_D_QUOTE
				|| tmp->type == T_S_QUOTE || tmp->type == T_ENV))
			ft_add_back_redi(&head, add_new(prev->type, tmp->token));
		prev = tmp;
		tmp = tmp->next;
	}
	return (head);
}
