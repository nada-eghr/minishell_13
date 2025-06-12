/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 14:44:47 by naessgui          #+#    #+#             */
/*   Updated: 2025/06/02 14:46:02 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_herdoc_files(t_token *list)
{
    int count = 0;
    t_token *tmp= list;
    t_token *prev;
    
    prev = tmp ;
    tmp = tmp->next;
    while (tmp && tmp->type != TOKEN_PIPE)
    {
        if ((prev->type == TOKEN_HERDOC) && (tmp->type == TOKEN_WORD || tmp->type == TOKEN_QUOTED))
            count++;
        prev= tmp;
        tmp = tmp->next;
    }
    return count;
}
char **get_herdoc_files(t_token *token)
{
    t_token *tmp = token;
    t_token *prev;
    int i = 0;
    int count = count_herdoc_files(token);
    char **herdoc_files = malloc(sizeof(char *) * ( count + 2));
    if (!*herdoc_files)
        return NULL;
    prev= tmp;
    tmp = tmp->next;
    while (tmp && tmp->type != TOKEN_PIPE)
    {
        if ((prev->type == TOKEN_HERDOC) && (tmp->type == TOKEN_WORD || tmp->type == TOKEN_QUOTED))
        {
            herdoc_files[i] = strdup(tmp->token);
            i++;
        }
        prev = tmp ;
        tmp = tmp->next;
    }
    herdoc_files[i] = NULL;
    return (herdoc_files);
}