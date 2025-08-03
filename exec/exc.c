/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slamhaou <slamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 17:38:08 by slamhaou          #+#    #+#             */
/*   Updated: 2025/08/03 15:35:37 by slamhaou         ###   ########.fr       */
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
		return(my_exit(list->arg, &var->exit_stat,var->rd_fd) ,1);
	else if (str_cmp(list->arg[0], "echo"))
		return (my_echo(list->arg, &var->exit_stat), 1);
	return(0);	
}

int	 excut_comand(t_var	*var, t_cmd *list, t_env_list **list_env)
{

	if (var->i < var->num_cmd - 1)
	{
		if (pipe(var->pip_fd))
		{
			write_err("Minishell: ", "pipe error: ", NULL);
			perror(NULL);
			return (var->exit_stat = 1, 1);
		}
	}
	var->arr_id[var->i] = fork();
	if (var->arr_id[var->i] < 0)
	{
		wait_child(var);
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

void	more_comnd(t_cmd *list, t_env_list **list_env, t_var *var, int *arr_f)
{
	int	j;

	j = 0;
	var->rd_fd = FIRST_CMD;
	while (list)
	{
		var->last_in = NO_REDERCT;
		var->last_out = NO_REDERCT;	
		 rederection(list, var, arr_f, j);
		if (var->last_in == ERORR || var->last_out == ERORR || var->her_s == 1)
			var->last_out = NO_REDERCT;	
		if (excut_comand(var, list, &*list_env))
			return;
		list = list->next;
		var->i++;
	}
}
void	close_reder(t_var * var, int *arr_fd)
{
	int len;

	len = 0;
	if (var->last_in != NO_REDERCT)
		close(var->last_in);
	if (var->last_out >= 0)
		close(var->last_out);
	if (var->len_hrd > 0)
	{
		while (len > var->len_hrd)
			close(arr_fd[len++]);
		free(arr_fd);
	}
}
void	exc(t_cmd *list, t_env_list **list_env, t_var *var)
{
	int	*arr_fd_h;

	if (str_cmp(list->arg[0], "exit"))
		bilt_in(var, list, list_env);
	var->i = 0;
	var->her_s = 0;
	var->its_bilt = 0;
	var->rd_fd = NO_PIP;
	var->last_out = NO_REDERCT;
	var->last_in = NO_REDERCT;
	arr_id_pross(var, list);
	arr_fd_h = open_all_heredoc(list, var, *list_env);
	if (!list->next)
	{
		rederection(list, var, arr_fd_h, 0);
		if (var->last_in == ERORR || var->last_out == ERORR || var->her_s == 1)
		{	
			free(var->arr_id);
			close_reder(var, arr_fd_h);
			return ;
		}
		excut_comand(var, list, &*list_env);
	}
	else
		more_comnd(list, list_env, var, arr_fd_h);
	wait_child(var);
	close_reder(var, arr_fd_h);
}
