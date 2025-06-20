/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:48:55 by naessgui          #+#    #+#             */
/*   Updated: 2025/06/18 17:34:49 by naessgui         ###   ########.fr       */
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
	t_token *tmp = token;
	t_redirection *head ;
	t_redirection *node;

	head = NULL;
	node = NULL;
	t_token *prev;

	prev = tmp;
	tmp = tmp->next;
	while (tmp && tmp->type != TOKEN_PIPE)
	{
		if ((prev->type == TOKEN_REDIR_OUT || prev->type == TOKEN_APPEND
				|| prev->type == TOKEN_REDIR_IN || prev->type == TOKEN_HERDOC)
			&& (tmp->type == TOKEN_WORD || tmp->type == TOKEN_D_QUOTE ||  tmp->type == TOKEN_S_QUOTE ))
			ft_add_back_redi(&head, add_new(prev->type, tmp->token));
		prev = tmp;
		tmp = tmp->next;
	}

	return (head);
}
