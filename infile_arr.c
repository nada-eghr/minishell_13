/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_arr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 12:57:57 by naessgui          #+#    #+#             */
/*   Updated: 2025/06/13 13:28:20 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_in_arr(t_token *list)
{
    int count = 0;
    t_token *tmp= list;
    t_token *prev;
    
    prev = tmp ;
    tmp = tmp->next;
    while (tmp && tmp->type != TOKEN_PIPE)
    {
        if ((prev->type == TOKEN_REDIR_IN || prev->type == TOKEN_HERDOC) && (tmp->type == TOKEN_WORD || tmp->type == TOKEN_QUOTED))
            count++;
        prev= tmp;
        tmp = tmp->next;
    }
    return count;
}
int *infiles_flage(t_token *token)
{
    t_token *tmp = token;
    t_token *prev;
    int i = 0;
    int count = count_infiles(token);
    int  *arr_infiles = malloc(sizeof(int) * ( count + 1));
    if (!arr_infiles)
        return NULL;
    // for(int i = 0; i < count; i++)
    //     arr_infiles[i] = -1;
    prev= tmp;
    tmp = tmp->next;
    while (tmp && tmp->type != TOKEN_PIPE)
    {
        if ((prev->type == TOKEN_REDIR_IN ) && (tmp->type == TOKEN_WORD || tmp->type == TOKEN_QUOTED))
        {
            arr_infiles[i] = 0;
            i++;
        }
        else if ((prev->type == TOKEN_HERDOC) && (tmp->type == TOKEN_WORD || tmp->type == TOKEN_QUOTED))
        {
            arr_infiles[i] = 1;
            i++;
        }
        
        prev = tmp ;
        tmp = tmp->next;
    }
    arr_infiles[i] = -1;
    return (arr_infiles);
}