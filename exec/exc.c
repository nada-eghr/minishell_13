/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slamhaou <slamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 17:38:08 by slamhaou          #+#    #+#             */
/*   Updated: 2025/07/08 19:29:26 by slamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <sys/stat.h>

int		bilt_in(int	*exit_sta, t_cmd *list, t_env_list **list_env)
{
	if (!list->arg[0])
		return (1);
	if (str_cmp(list->arg[0], "pwd")|| str_cmp(list->arg[0], "PWD"))
		return(my_pwd(exit_sta), 1);
	else if (str_cmp(list->arg[0], "env"))
		return (my_env(*list_env, exit_sta), 1);
	else if (str_cmp(list->arg[0], "cd"))
		return(my_cd(*list_env,list->arg, exit_sta), 1);
	else if (str_cmp(list->arg[0], "unset"))
		return(my_unset(list_env,list->arg), 1);
	else if (str_cmp(list->arg[0], "export"))
		return(my_export(*list_env,list->arg), 1);
	else if (str_cmp(list->arg[0], "exit"))
		my_exit(list->arg, exit_sta);
	else if (str_cmp(list->arg[0], "echo"))
		return (my_echo(list->arg, exit_sta), 1);
	return(0);	
}

void	my_child(t_var *var, t_cmd *list, t_env_list *list_env)
{
	char	**env_arr;
	char	*path;
	
	path = it_correct_comnd(&var->exit_stat,list->arg[0], list_env);
	if (!path)
		exit (var->exit_stat);
	env_arr = return_list_to_arg(list_env); // convert t_env to char **
	if (var->rd_fd != NO_PIP) // if we have PIPE
	{	
		if (var->rd_fd != FIRST_CMD)
		{
			dup2(var->rd_fd, 0);
			close(var->rd_fd);
		}
		if (var->i < var->num_cmd - 1) // if we are not in the last cmd
		{
			dup2(var->pip_fd[1], 1);
			close(var->pip_fd[1]);
		}
	}
	if (var->last_in >= 0)
	{
		dup2(var->last_in, 0);
		close(var->last_in);
	}
	if (var->last_out >= 0)
	{
		dup2(var->last_out, 1);
		close(var->last_out);
	}
	if (execve(path, list->arg, env_arr) < 0)
	{
		free(env_arr);
		exit (127);
	}
}

void	 excut_comand(t_var	*var, t_cmd *list, t_env_list **list_env)
{

	if (bilt_in(&var->exit_stat,list, &*list_env))
		return ;// bilt in in the child case of pipe;
	if (var->i < var->num_cmd - 1)
		pipe(var->pip_fd);
	var->id_pros = fork();
	if (var->id_pros < 0)
		return ;
	if (var->id_pros == 0)
		my_child(var, list, *list_env);
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
	if (var->i < var->num_cmd)
	{
		var->arr_id[var->i] = var->id_pros;
		var->i++;
	}
}

void	arr_id_pross(t_var *var, t_cmd *list)
{
	int		counter;

	counter = 0;
	while (list)
	{
		counter++;
		list = list->next;
	}
	var->num_cmd = counter;
	if (counter == 0)
		return;
	var->arr_id = malloc(sizeof(int) * counter);
}
void	wait_child(t_var *var)
{
	int i;
	int	stat;
	
	i = 0;
	while (i < var->num_cmd)
	{
		waitpid(var->arr_id[i], &stat, 0);
		if (i == var->num_cmd - 1)
			var->exit_stat =  WEXITSTATUS(stat);
		i++;
	}
}
void	exc(t_cmd *list, t_env_list **list_env)
{
	t_var	var;
	int stat;

	var.i = 0;
	var.rd_fd = NO_PIP;
	arr_id_pross(&var, list);
	if (!list->next)
	{
		rederection(list, &var);
		if (var.last_in == ERORR || var.last_out == ERORR)
			return;
		excut_comand(&var, list, &*list_env);
		wait(&stat);
		return ;
	}
	var.rd_fd = FIRST_CMD;
	while (list)
	{
		rederection(list, &var);
		if (var.last_in == ERORR || var.last_out == ERORR)
			return ;
		excut_comand(&var, list, &*list_env);
		list = list->next;
		// var.i++;
	}
	wait_child(&var);
}
