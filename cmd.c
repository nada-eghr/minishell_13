/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:54:08 by naessgui          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/06/13 15:58:16 by naessgui         ###   ########.fr       */
=======
/*   Updated: 2025/06/12 19:05:55 by naessgui         ###   ########.fr       */
>>>>>>> 05a0283f39f744cb5e626e050f696d346ca0144c
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

t_cmd *creat_cmd(t_token *list)
{
    t_cmd *cmd = (t_cmd*)malloc(sizeof(t_cmd));
<<<<<<< HEAD
    t_infiles *infile = (t_infiles*)
    if (!cmd)
        return NULL;
    cmd->arg = get_args(list);
    cmd-> infile->infiles = get_infiles(list);
    cmd->infile->infile_flag = infiles_flage(list);
    //cmd->append = get_append_files(list);
    cmd->outfile->outfile_flag = outfiles_flage(list);
    cmd->outfile->outfiles = get_outfiles(list);
=======
    if (!cmd)
        return NULL;
    cmd->arg = get_args(list);
    cmd->infile = get_infiles(list);
    cmd->append = get_append_files(list);
    cmd->outfile = get_outfiles(list);
>>>>>>> 05a0283f39f744cb5e626e050f696d346ca0144c
    cmd->herdoc = get_herdoc_files(list);
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