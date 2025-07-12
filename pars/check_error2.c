/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 14:44:47 by naessgui          #+#    #+#             */
/*   Updated: 2025/07/12 16:06:53 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// static bool	check_pipe(t_token **list)
// {
// 	t_token	*tmp;

// 	tmp = *list;
// 	if (!tmp)
// 		return (true);
// 	if (tmp->type == T_PIPE)
// 	{
// 		return (true);
// 	}
// 	while (tmp)
// 	{
// 		if (tmp->type == T_PIPE && tmp->next
// 			&& tmp->next->type == T_PIPE)
// 			return (true);
// 		if (tmp->type == T_PIPE && tmp->next == NULL)
// 			return (true);
// 		tmp = tmp->next;
// 	}
// 	return (false);
// }

static bool check_redirections(t_token **list)
{
    t_token *current = *list;

    if (!current)
        return (false);
    
    while (current)
    {
        if (current->type == T_RED_IN || current->type == T_RED_OUT ||
            current->type == T_APPEND || current->type == T_HEREDOC)
        {
            // Cas 1: Pas de token après la redirection
            if (current->next == NULL)
            {
                *list = current; // Pointeur vers le token problématique
                return (true);
            }
            
            // Cas 2: Token suivant invalide
            if (current->next->type != T_WORD && current->next->type != T_D_QUOTE &&
                current->next->type != T_S_QUOTE && current->next->type != T_ENV)
            {
                *list = current; // Pointeur vers le token problématique
                return (true);
            }
        }
        current = current->next;
    }
    return (false);
}

static bool check_pipe(t_token **list)
{
    t_token *current = *list;

    // Cas 1: Pipe en première position
    if (current && current->type == T_PIPE)
    {
        *list = current;
        return (true);
    }

    while (current)
    {
        // Cas 2: Pipe sans commande avant ou après
        if (current->type == T_PIPE)
        {
            if (current->next == NULL || current->next->type == T_PIPE)
            {
                *list = current;
                return (true);
            }
        }
        current = current->next;
    }
    return (false);
}

bool check_error1(t_token **list)
{
    t_token *save = *list;

    if (check_pipe(list))
    {
        if ((*list)->next && (*list)->next->type == T_PIPE)
            printf("minishell: syntax error near unexpected token `|'\n");
        else if (*list && (*list)->type == T_PIPE && (*list)->next == NULL)
            printf("minishell: syntax error near unexpected token `|'\n");
        else if (*list && (*list)->type == T_PIPE)
            printf("minishell: syntax error near unexpected token `|'\n");
        return (true);
    }

    *list = save; // Réinitialiser pour check_redirections
    if (check_redirections(list))
    {
        if (*list && (*list)->next == NULL)
            printf("minishell: syntax error near unexpected token `newline'\n");
        else if (*list && (*list)->next)
            printf("minishell: syntax error near unexpected token `%s'\n", (*list)->next->token);
        return (true);
    }

    return (false);
}