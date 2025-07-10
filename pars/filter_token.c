/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 17:15:41 by naessgui          #+#    #+#             */
/*   Updated: 2025/07/10 22:01:58 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void deleteSpecificNode(t_token** head, t_token* nodeToDelete) {
    if (*head == NULL || nodeToDelete == NULL) {
        return; // Retour silencieux pour les cas d'erreur
    }

    // Cas spécial: suppression de la tête
    if (*head == nodeToDelete) {
        *head = (*head)->next;
        free(nodeToDelete);
        return;
    }

    // Recherche du nœud précédent
    t_token* current = *head;
    while (current != NULL && current->next != nodeToDelete) {
        current = current->next;
    }

    // Si on a trouvé le nœud précédent
    if (current != NULL) {
        current->next = nodeToDelete->next;
        free(nodeToDelete);
    }
}

t_token *convert_to_token(t_token *token)
{
    t_token *current = token;
    t_token *prev = NULL;
    t_token *to_delete = NULL;

    while (current)
    {
        if (current->type == T_SPACE)
        {
            to_delete = current;
            current = current->next;
            
            if (prev == NULL) {
                // Suppression de la tête
                token = current;
            } else {
                prev->next = current;
            }
            
            deleteSpecificNode(&token, to_delete);
        }
        else
        {
            prev = current;
            current = current->next;
        }
    }
    return token;
}
// char	*filter_token(t_token *filter_lst)
// {
// 	t_token	*token;
// 	char	*str;

// 	str = ft_strdup("");
// 	token = filter_lst;
// 	while (token)
// 	{
// 		str = ft_strjoin(str, token->token);
// 		token = token->next;
// 	}
// 	return (str);
// }

// static t_token	*parse_operator_token1(const char *data, int *i)
// {
// 	int		j;
// 	char	tmp[3];

// 	j = 0;
// 	if (!data || !data[*i])
// 		return (NULL);
// 	if (((data[*i] == '>' && data[*i + 1] == '>') || (data[*i] == '<' 
// 				&& data[*i + 1] == '<')) && data[*i] != '|')
// 		tmp[j++] = data[(*i)++];
// 	tmp[j++] = data[(*i)++];
// 	tmp[j] = '\0';
// 	return (creattoken(tmp));
// }

// static t_token	*parse_word_token1(const char *data, int *i)
// {
// 	int		start;
// 	int		end;
// 	char	*new;
// 	t_token	*token;

// 	start = *i;
// 	while (data[*i] && !ft_space(data[*i]) && data[*i] != '>' && data[*i] != '<'
// 		&& data[*i] != '|')
// 		(*i)++;
// 	end = *i;
// 	new = substr(data, start, end - start);
// 	token = creattoken(new);
// 	free(new);
// 	return (token);
// }

// t_token	*convert_to_token(char *data)
// {
// 	int		i;
// 	t_token	*head;
// 	t_token	*token;

// 	i = 0;
// 	head = NULL;
// 	token = NULL;
// 	while (data[i])
// 	{
// 		if (data[i] && ft_space(data[i]))
// 		{
// 			while (ft_space(data[i]))
// 				i++;
// 		}
// 		else if (data[i] == '>' || data[i] == '<' || data[i] == '|')
// 			token = parse_operator_token1(data, &i);
// 		else
// 			token = parse_word_token1(data, &i);
// 		if (token)
// 		{
// 			add_back(&head, token);
// 			token = NULL;
// 		}
// 	}
// 	return (head);
// }
