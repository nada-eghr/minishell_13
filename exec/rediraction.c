/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rediraction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slamhaou <slamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 13:27:05 by slamhaou          #+#    #+#             */
/*   Updated: 2025/07/29 11:06:14 by slamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	in_file(int type, char *file, int *last_in)
{
	if (type == T_RED_IN)
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
	 if (type == T_RED_OUT)
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
	else if (type == T_APPEND)
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

void	rederection(t_cmd *list, t_var *var, t_env_list *list_env)
{
	t_redirection	*rid;
	int				fd_in;
	int				fd_out;

	(void)list_env;
	rid = list->redi;
	fd_in = var->last_in;
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
	if (fd_in == ERORR)
		var->exit_stat = 1;
	if (fd_out == ERORR)	
		var->exit_stat = 1;
	var->last_in = fd_in;
	var->last_out = fd_out;
}
