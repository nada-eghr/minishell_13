/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 11:56:55 by naessgui          #+#    #+#             */
/*   Updated: 2025/06/13 13:23:10 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_out_arr(t_token *list)
{
    int count = 0;
    t_token *tmp= list;
    t_token *prev;
    
    prev = tmp ;
    tmp = tmp->next;
    while (tmp && tmp->type != TOKEN_PIPE)
    {
        if ((prev->type == TOKEN_REDIR_OUT || prev->type == TOKEN_APPEND) && (tmp->type == TOKEN_WORD || tmp->type == TOKEN_QUOTED))
            count++;
        prev= tmp;
        tmp = tmp->next;
    }
    return count;
}
int *outfiles_flage(t_token *token)
{
    t_token *tmp = token;
    t_token *prev;
    int i = 0;
    int count = count_outfiles(token);
    int  *arr_outfiles = malloc(sizeof(int) * ( count + 1));
    if (!arr_outfiles)
        return NULL;
    prev= tmp;
    tmp = tmp->next;
    while (tmp && tmp->type != TOKEN_PIPE)
    {
        if ((prev->type == TOKEN_REDIR_OUT ) && (tmp->type == TOKEN_WORD || tmp->type == TOKEN_QUOTED))
        {
            arr_outfiles[i] = 0;
            i++;
        }
        else if ((prev->type == TOKEN_APPEND) && (tmp->type == TOKEN_WORD || tmp->type == TOKEN_QUOTED))
        {
            arr_outfiles[i] = 1;
            i++;
        }
        
        prev = tmp ;
        tmp = tmp->next;
    }
    arr_outfiles[i] = -1;
    return (arr_outfiles);
}