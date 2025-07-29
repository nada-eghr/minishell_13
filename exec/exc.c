/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slamhaou <slamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 17:38:08 by slamhaou          #+#    #+#             */
/*   Updated: 2025/07/26 10:30:07 by slamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <sys/stat.h>

int		bilt_in(t_var *var, t_cmd *list, t_env_list **list_env)
{
	if (!list->arg[0])
		return (1);
	if (str_cmp(list->arg[0], "pwd")|| str_cmp(list->arg[0], "PWD"))
		return(my_pwd(&var->exit_stat), 1);
	else if (str_cmp(list->arg[0], "env"))
		return (my_env(*list_env, &var->exit_stat), 1);
	else if (str_cmp(list->arg[0], "cd"))
		return(my_cd(*list_env,list->arg, &var->exit_stat), 1);
	else if (str_cmp(list->arg[0], "unset"))
		return(my_unset(list_env,list->arg, &var->exit_stat), 1);
	else if (str_cmp(list->arg[0], "export"))
		return(my_export(*list_env,list->arg, &var->exit_stat), 1);
	else if (str_cmp(list->arg[0], "exit"))
		my_exit(list->arg, &var->exit_stat,var->rd_fd);
	else if (str_cmp(list->arg[0], "echo"))
		return (my_echo(list->arg, &var->exit_stat), 1);
	return(0);	
}

int	 excut_comand(t_var	*var, t_cmd *list, t_env_list **list_env)
{
	char *sv_er;
	
	if (var->rd_fd == NO_PIP && bilt_in(var,list, &*list_env))
	{
		var->its_bilt = 1;
		return 0;
	}
	if (var->i < var->num_cmd - 1)
	{
		if (pipe(var->pip_fd))
		{
			write_err("Minishell: ", "pipe error: ", NULL);
			perror(NULL);
			//wait(0);
			return (var->exit_stat = 1, 1);
		}
	}
	var->arr_id[var->i] = fork();
	if (var->arr_id[var->i] < 0)
	{
		wait_child(var);
		sv_er = strerror(errno);
		write_err("Minishell: ", "fork", ": ");
		perror(NULL);
		var->exit_stat = 1;
		return 1;
	}
	if (var->arr_id[var->i] == 0)
		my_child(var, list, list_env);
	else
	{
		if (var->rd_fd != NO_PIP)
		{
			if (var->rd_fd != FIRST_CMD)
				close(var->rd_fd);
			if (var->i < var->num_cmd - 1)
			{
				close(var->pip_fd[1]);
				var->rd_fd = var->pip_fd[0];
	
			}
		}
	}
	return (0);
}

void	 exc(t_cmd *list, t_env_list **list_env, t_var *var)
{
	var->i = 0;
	var->its_bilt = 0;
	var->rd_fd = NO_PIP;
	var->her_s = 0;
	sigg = 0;
	arr_id_pross(var, list);
	if (!list->next)
	{
		rederection(list, var, *list_env);
		if (var->last_in == ERORR || var->last_out == ERORR || var->her_s == 1)
		{		
			free(var->arr_id);
			return;
		}
		excut_comand(var, list, &*list_env);
	}
	else
	{
		var->rd_fd = FIRST_CMD;
		while (list)
		{
			rederection(list, var, *list_env);
			if (var->last_in == ERORR || var->last_out == ERORR || var->her_s == 1)
				return ;
			if (excut_comand(var, list, &*list_env))
				return ;
			list = list->next;
			var->i++;
		}
	}
	wait_child(var);
}
