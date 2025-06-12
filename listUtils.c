/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listUtils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 13:00:43 by naessgui          #+#    #+#             */
/*   Updated: 2025/06/12 19:41:15 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

t_token* creattoken(char *data)
{
	
	t_token *newnode= (t_token*)malloc(sizeof(t_token));
	if (!newnode)
		return NULL;
	newnode->token =  strdup(data);
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

void printLinkedList(t_token* head)
{
    t_token* current = head;
    while (current != NULL) {
        printf("%s -> ", current->token);
		// print_arg
        current = current->next;
    }
    printf("NULL\n");
}
void print_node_cmd(t_cmd *node_cmd)
{
	int i = 0;
	t_cmd *tmp = node_cmd;
	while ( tmp->arg[i])
	{
		printf("%s\n", tmp->arg[i]);
		i++;
	}
	printf("NULL");
}

void ll()
{
    system("leaks -q a.out");
}


void free_list(t_token *head)
{
    t_token *current = head;
    t_token *next_node;

    while (current != NULL) {
        next_node = current->next;
        free(current->token);
        free(current);
        current = next_node;
    }
}