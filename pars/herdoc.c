/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 14:44:47 by naessgui          #+#    #+#             */
/*   Updated: 2025/07/01 12:33:08 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check(t_token *token)
{
	t_token	*tmp;
	t_token	*prev;
	int		herdoc;

	herdoc = 0;
	tmp = token;
	prev = tmp;
	tmp = tmp->next;
	while (tmp && tmp->type != T_PIPE)
	{
		if ((prev->type == T_HEREDOC) && (tmp->type == T_WORD
				|| tmp->type == T_D_QUOTE || tmp->type == T_S_QUOTE))
			herdoc = 1;
		prev = tmp;
		tmp = tmp->next;
	}
	return (herdoc);
}
