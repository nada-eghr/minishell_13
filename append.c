/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 14:42:13 by naessgui          #+#    #+#             */
/*   Updated: 2025/06/02 14:44:34 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_append_files(t_token *list)
{
    int count = 0;
    t_token *tmp= list;
    t_token *prev;
    
    prev = tmp ;
    tmp = tmp->next;
    while (tmp && tmp->type != TOKEN_PIPE)
    {
        if ((prev->type == TOKEN_APPEND) && (tmp->type == TOKEN_WORD || tmp->type == TOKEN_QUOTED))
            count++;
        prev= tmp;
        tmp = tmp->next;
    }
    return count;
}
char **get_append_files(t_token *token)
{
    t_token *tmp = token;
    t_token *prev;
    int i = 0;
    int count = count_append_files(token);
    char **append_files = malloc(sizeof(char *) * ( count + 2));
    if (!*append_files)
        return NULL;
    prev= tmp;
    tmp = tmp->next;
    while (tmp && tmp->type != TOKEN_PIPE)
    {
        if ((prev->type == TOKEN_APPEND) && (tmp->type == TOKEN_WORD || tmp->type == TOKEN_QUOTED))
        {
            append_files[i] = strdup(tmp->token);
            i++;
        }
        prev = tmp ;
        tmp = tmp->next;
    }
    append_files[i] = NULL;
    return (append_files);
}