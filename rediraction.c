/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rediraction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slamhaou <slamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 13:27:05 by slamhaou          #+#    #+#             */
/*   Updated: 2025/06/23 13:20:58 by slamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heder_shell.h"

void	list_rediraction(t_redirection *redi, t_var *var)
{
	t_redirection *lst_in;
	t_redirection *lst_out;
	t_redirection *redi2;

	redi2 = redi;
	lst_in = NULL;
	lst_out = NULL;
	while (redi2)
	{
		if (redi2->type == TOKEN_REDIR_IN)
			lst_in = redi2;
		else if (redi2->type == TOKEN_REDIR_OUT)
			lst_out = redi2;
		redi2 = redi2->next;
	}
	
}
void	rederection(t_cmd *list, t_var *var)
{
	int fd;

	fd = 0;
	if (list->herdoc == 1)
		//open_herdok()
		fd = 0;
	list_rediraction(list->redi, var);
}