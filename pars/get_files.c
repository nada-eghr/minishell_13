/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:48:55 by naessgui          #+#    #+#             */
/*   Updated: 2025/07/12 12:54:04 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


t_redirection *add_new(int type, char *file_name, int her_doc)
{
    t_redirection *node;

    node = malloc(sizeof(t_redirection));
    if (!node)
        return (NULL);
    node->type = type;
    node->her_doc = her_doc;
    node->file = ft_strdup(file_name);
    if (!node->file)
    {
        free(node);
        return (NULL);
    }
    node->next = NULL;
    return (node);
}

void ft_add_back_redi(t_redirection **head, t_redirection *node)
{
    t_redirection *tmp;

    if (!*head)
    {
        *head = node;
        return;
    }
    tmp = *head;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = node;
}

static int is_file_token(int type)
{
    return (type == T_WORD || type == T_D_QUOTE || 
            type == T_S_QUOTE || type == T_ENV);
}

static int is_redirection_token(int type)
{
    return (type == T_RED_OUT || type == T_APPEND || 
            type == T_RED_IN || type == T_HEREDOC);
}

t_redirection *get_files(t_second_token *token)
{
    t_second_token *tmp;
    t_redirection *head;
    t_redirection *node;
    t_second_token *prev;

    if (!token)
        return (NULL);
    
    head = NULL;
    prev = token;
    tmp = token->next;
    
    while (tmp && tmp->type != T_PIPE)
    {
        if (is_redirection_token(prev->type) && is_file_token(tmp->type))
        {
            int h = 0;
            if (prev->type == T_HEREDOC && (tmp->type == T_S_QUOTE || tmp->type == T_D_QUOTE))
            {
                    h = 1;
            }
            node = add_new(prev->type, tmp->token, h);
            if (!node)
            {
                // Ici il faudrait libérer toute la liste en cas d'erreur
                return (NULL);
            }
            ft_add_back_redi(&head, node);
        }
        prev = tmp;
        tmp = tmp->next;
    }
    return (head);
}
