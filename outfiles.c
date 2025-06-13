/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfiles.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:48:55 by naessgui          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/06/13 12:08:10 by naessgui         ###   ########.fr       */
=======
/*   Updated: 2025/06/02 13:52:35 by naessgui         ###   ########.fr       */
>>>>>>> 05a0283f39f744cb5e626e050f696d346ca0144c
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_outfiles(t_token *list)
{
    int count = 0;
    t_token *tmp= list;
    t_token *prev;
    
    prev = tmp ;
    tmp = tmp->next;
    while (tmp && tmp->type != TOKEN_PIPE)
    {
<<<<<<< HEAD
        if ((prev->type == TOKEN_REDIR_OUT || prev->type == TOKEN_APPEND ) && (tmp->type == TOKEN_WORD || tmp->type == TOKEN_QUOTED))
=======
        if ((prev->type == TOKEN_REDIR_OUT) && (tmp->type == TOKEN_WORD || tmp->type == TOKEN_QUOTED))
>>>>>>> 05a0283f39f744cb5e626e050f696d346ca0144c
            count++;
        prev= tmp;
        tmp = tmp->next;
    }
    return count;
}
char **get_outfiles(t_token *token)
{
    t_token *tmp = token;
    t_token *prev;
    int i = 0;
    int count = count_outfiles(token);
    char **outfiles = malloc(sizeof(char *) * ( count + 2));
    if (!*outfiles)
        return NULL;
    prev= tmp;
    tmp = tmp->next;
    while (tmp && tmp->type != TOKEN_PIPE)
    {
<<<<<<< HEAD
        if ((prev->type == TOKEN_REDIR_OUT || prev->type == TOKEN_APPEND) && (tmp->type == TOKEN_WORD || tmp->type == TOKEN_QUOTED))
=======
        if ((prev->type == TOKEN_REDIR_OUT) && (tmp->type == TOKEN_WORD || tmp->type == TOKEN_QUOTED))
>>>>>>> 05a0283f39f744cb5e626e050f696d346ca0144c
        {
            outfiles[i] = strdup(tmp->token);
            i++;
        }
        prev = tmp ;
        tmp = tmp->next;
    }
    outfiles[i] = NULL;
    return (outfiles);
}