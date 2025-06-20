/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 12:03:57 by naessgui          #+#    #+#             */
/*   Updated: 2025/06/20 17:45:47 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdbool.h>

bool	check_pipe(t_token **list)
{
	t_token	*tmp;

	tmp = *list;
	if (!tmp)
		return (true);
	if (tmp->type == TOKEN_PIPE)
	{
		return (true);
	}
	while (tmp)
	{
		if (tmp->type == TOKEN_PIPE && tmp->next
			&& tmp->next->type == TOKEN_PIPE)
			return (true);
		if (tmp->type == TOKEN_PIPE && tmp->next == NULL)
			return (true);
		tmp = tmp->next;
	}
	return (false);
}
//------------------------------------------------

bool	check_unclosed_quotes(t_token *tokens)
{
	t_token	*tmp;
	int		len;
	char	first ;
	char	last;

	tmp = tokens;
	while (tmp)
	{
		len = ft_strlen(tmp->token);
		if (len >= 1)
		{
			first = tmp->token[0];
			last = tmp->token[len - 1];
			if ((first == '"' || first == '\'') && last != first)
			{
				// opening quote with no matching closing quote
				return (true);
			}
		}
		tmp = tmp->next;
	}
	return (false);
}

bool	check_redirections(t_token **list)
{
	t_token	*tmp;

	tmp = *list;
	if (!tmp)
		return (true);
	while (tmp)
	{
		if ((tmp->type == TOKEN_REDIR_IN || tmp->type == TOKEN_REDIR_OUT
				|| tmp->type == TOKEN_APPEND || tmp->type == TOKEN_HERDOC))
		{
			if (tmp->next == NULL)
				return (true);
			else if (tmp->next->type != TOKEN_WORD && tmp->next->type != TOKEN_D_QUOTE && tmp->next->type != TOKEN_S_QUOTE && tmp->next->type != TOKEN_ENV_VAR )
				return (true);
		}
		// if (ft_strcmp(tmp->token, "<>") == 0)
		// 	return (true);
		tmp = tmp->next;
	}
	return (false);
}

bool	check_error(t_token **list)
{
	if (check_redirections(list))
	{
		printf("minishell : syntax error near unexpected token `newline'\n");
		return (true);
	}
	if (check_pipe(list) == 1)
	{
		printf("minishell : syntax error near unexpected token `|'\n");
		return (true);
	}
	// if(check_unclosed_quotes(*list))
	// {
	//     printf("syntaxe error quotes");
	//     return (true);
	// }
	return (false);
}
// &&  tmp->next && (tmp->next->type != TOKEN_WORD
// && tmp->next->type != TOKEN_QUOTED) )
//             return (true);