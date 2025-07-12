/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_tokinization.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 11:33:36 by naessgui          #+#    #+#             */
/*   Updated: 2025/07/12 13:23:24 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_second_token *second_tokinization(t_token *token ) {
    t_token *tmp = token;
    t_second_token *head = NULL;
    t_second_token *new_node;
    char *str = ft_strdup("");

    while (tmp) {
        if (tmp->type == T_WORD || tmp->type == T_ENV || 
            tmp->type == T_S_QUOTE || tmp->type == T_D_QUOTE) {
            free(str);
            str = ft_strdup("");
            while (tmp && (tmp->type == T_WORD || tmp->type == T_ENV || 
                          tmp->type == T_S_QUOTE || tmp->type == T_D_QUOTE)) {
                str = ft_strjoin(str, tmp->token);
                tmp = tmp->next;
            }
            new_node = creat_second_token(str, T_WORD);
            add_b(&head, new_node);
            continue;
        }
        else if (tmp->type == T_PIPE || tmp->type == T_RED_IN || 
                tmp->type == T_RED_OUT || tmp->type == T_APPEND || 
                tmp->type == T_HEREDOC) {
            new_node = creat_second_token(tmp->token, tmp->type);
            add_b(&head, new_node);
        }
        tmp = tmp->next;
    }
    
    free(str); 
    return head;
}