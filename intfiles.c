/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intfiles.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 13:07:00 by naessgui          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/06/13 13:25:33 by naessgui         ###   ########.fr       */
=======
/*   Updated: 2025/06/02 13:31:30 by naessgui         ###   ########.fr       */
>>>>>>> 05a0283f39f744cb5e626e050f696d346ca0144c
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int count_infiles(t_token *list)
{
    int count = 0;
    t_token *tmp = list;
    t_token *prev;
    
    prev = tmp;
    tmp = tmp->next;
    while (tmp && tmp->type != TOKEN_PIPE)
    {
<<<<<<< HEAD
        if ((prev->type == TOKEN_REDIR_IN ||  prev->type == TOKEN_HERDOC) && (tmp->type == TOKEN_WORD || tmp->type == TOKEN_QUOTED))
=======
        if ((prev->type == TOKEN_REDIR_IN) && (tmp->type == TOKEN_WORD || tmp->type == TOKEN_QUOTED))
>>>>>>> 05a0283f39f744cb5e626e050f696d346ca0144c
            count++;
        prev = tmp;
        tmp = tmp->next;
    }
    return count;


}

   
char **get_infiles(t_token *token)
{
    t_token *tmp =token;
    t_token *prev;
    int i = 0;
    int count = count_infiles(token);
    char **infiles = malloc(sizeof(char *) * (count + 2));
    if (!*infiles)
        return NULL;
    prev = tmp;
    tmp = tmp->next;
    while (tmp && tmp->type != TOKEN_PIPE) 
    {
<<<<<<< HEAD
        if (( prev->type == TOKEN_REDIR_IN || prev->type == TOKEN_HERDOC)  && (tmp->type == TOKEN_WORD || tmp->type == TOKEN_QUOTED))
=======
        if (( prev->type == TOKEN_REDIR_IN) && (tmp->type == TOKEN_WORD || tmp->type == TOKEN_QUOTED))
>>>>>>> 05a0283f39f744cb5e626e050f696d346ca0144c
        {
            
            infiles[i] = strdup(tmp->token);
            // printf("infiles[%d],%s\n",i,infiles[i]);
            i++;
        }
        prev = tmp ;
        tmp = tmp->next;
    }
    infiles[i] = NULL;
    return (infiles);   
} 