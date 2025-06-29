/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rediraction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slamhaou <slamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 13:27:05 by slamhaou          #+#    #+#             */
/*   Updated: 2025/06/29 18:35:25 by slamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heder_shell.h"

void	in_file(int type, char *file, int *last_in)
{
	if (type == TOKEN_REDIR_IN)
	{
		if (*last_in >= 0)
			close(*last_in);
		*last_in = open(file, O_RDONLY);
		if (*last_in < 0)
		{
			write_err("Minishell: ", file, ": ");
			perror(NULL);
			*last_in = ERORR;
			return ;
		}
	}
}
                                                                                                                                     
void	out_file(int type, char *file , int *last_out)
{
		 if (type == TOKEN_REDIR_OUT)
		{
			if (last_out >= 0)
				close(*last_out);
			*last_out = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0664);
			if (*last_out < 0)
			{
				write_err("Minishell: ", file, ": ");
				perror(NULL);
				*last_out = ERORR;
			}
		}
		else if (type == TOKEN_APPEND)
		{
			if (last_out >= 0)
				close(*last_out);
			*last_out = open(file, O_CREAT | O_APPEND | O_WRONLY,0664);
			if (*last_out < 0)
			{
				write_err("Minishell: ", file,": ");
				perror(NULL);
				*last_out = ERORR;
			}
		}
}

void	rederection(t_cmd *list, t_var *var)
{
	t_redirection *rid;
	int fd_in;
	int	fd_out;

	// if (list->herdoc == 1)
	// 	//open_herdok()
	rid = list->redi;
	fd_in = NO_REDERCT;
	fd_out = NO_REDERCT;
	while (rid)
	{
		in_file(rid->type, rid->file, &fd_in);
		if (fd_in == ERORR)
		 	break;
		out_file(rid->type, rid->file, &fd_out);
		if (fd_out == ERORR)
			break;
		rid = rid->next;
	}
	var->last_in = fd_in;
	var->last_out = fd_out;
}
