/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slamhaou <slamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 14:44:47 by naessgui          #+#    #+#             */
/*   Updated: 2025/07/02 17:19:44 by slamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check(t_token *token)
{
	t_token	*tmp;
	t_token	*prev;
	int		herdoc;

	herdoc = 0;
	tmp = token;
	prev = tmp;
	tmp = tmp->next;
	while (tmp && tmp->type != TOKEN_PIPE)
	{
		if ((prev->type == TOKEN_HERDOC) && (tmp->type == TOKEN_WORD
				|| tmp->type == TOKEN_D_QUOTE || tmp->type == TOKEN_S_QUOTE ))
			herdoc = 1;
		prev = tmp;
		tmp = tmp->next;
	}
	return (herdoc);
}

