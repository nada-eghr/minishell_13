/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:54:08 by naessgui          #+#    #+#             */
/*   Updated: 2025/06/14 17:20:31 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

t_cmd *creat_cmd(t_token *list)
{
    t_cmd *cmd = (t_cmd*)malloc(sizeof(t_cmd));
    if (!cmd)
        return NULL;
    cmd->arg = get_args(list);
    cmd->redi = get_files(list);
    cmd->herdoc = check(list);
    cmd->next = NULL;
    return (cmd);
}
void	add_back_cmd(t_cmd **head, t_cmd *node)
{
	t_cmd	*tmp;

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
t_cmd *list_cmd(t_token *tokens) 
{
    t_cmd *node_cmd = NULL;
    t_cmd *head  = NULL;
    t_token *curr = tokens;
    t_token *prev ;

    node_cmd = creat_cmd(curr);
    add_back_cmd(&head, node_cmd );
    prev = curr;
    curr = curr->next;
    while(curr)
    {
        if  (prev->type == TOKEN_PIPE)
        {
              node_cmd = creat_cmd(curr);
              add_back_cmd(&head,node_cmd);
       
        }
        prev = curr;
       curr = curr->next; 
    }
    return (head);
    
}
void print_cmd(t_cmd *node_cmd)
{
	int i;
	while(node_cmd)
	{
		i = 0;
		printf("command -->");
		while(node_cmd->arg[i])
		{
			printf(" [ %s ] ", node_cmd->arg[i++]);	
		}
		printf("\n");
		while(node_cmd->redi)
		{
			printf("type : [ %d ] <-------> file : [ %s ] \n", node_cmd->redi->type, node_cmd->redi->file);
			node_cmd->redi = node_cmd->redi->next;
		}
		node_cmd = node_cmd->next;
	}
}