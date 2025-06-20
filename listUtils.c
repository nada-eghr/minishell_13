/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listUtils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 13:00:43 by naessgui          #+#    #+#             */
/*   Updated: 2025/06/16 20:16:53 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*creattoken(char *data)
{
	t_token	*newnode;
	int		len;

	newnode = (t_token *)malloc(sizeof(t_token));
	if (!newnode)
		return (NULL);
	newnode->token = ft_strdup(data);
	len = ft_strlen(newnode->token);
	// printf("token [0] = %c\n", newnode->token[0]);
	// printf("token [len - 1] = %c\n", newnode->token[len - 1]);
	newnode->type = get_token_type(data);
	newnode->next = NULL;
	return (newnode);
}

void	add_back(t_token **head, t_token *node)
{
	t_token	*tmp;

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

void	printlinkedlist(t_token *head)
{
	t_token	*current;

	current = head;
	while (current != NULL)
	{
		printf("%s -> ", current->token);
		current = current->next;
	}
	printf("NULL\n");
}

void	ll(void)
{
	system("leaks -q a.out");
}

void	free_list(t_token *head)
{
	t_token	*current;
	t_token	*next_node;

	current = head;
	while (current != NULL)
	{
		next_node = current->next;
		free(current->token);
		free(current);
		current = next_node;
	}
}
