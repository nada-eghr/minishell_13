/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slamhaou <slamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 17:38:08 by slamhaou          #+#    #+#             */
/*   Updated: 2025/07/02 17:20:39 by slamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exit_sta = 0;

char	*it_correct_comnd(char *cmd, t_env_list *env)
{
	char	*path;
	char	**split_path;
	char	*new_p;
	int i;

	i = 0;
	path = my_get_env("PATH", env);
	split_path = ft_split(path, ':');
	while (split_path[i])
	{
		new_p = str_join(split_path[i], cmd, '/');
		if (access(new_p, X_OK) == 0)
		{
			free_tab(split_path);	
			return(new_p);
		}
		free(new_p);
		i++;
	}
	free_tab(split_path);
	return (NULL);
}
int		bilt_in(t_cmd *list, t_env_list **list_env)
{
	if (str_cmp(list->arg[0], "pwd")|| str_cmp(list->arg[0], "PWD"))
		return(my_pwd(), 1);
	else if (str_cmp(list->arg[0], "env"))
		return (my_env(*list_env), 1);
	else if (str_cmp(list->arg[0], "cd"))
		return(my_cd(*list_env,list->arg), 1);
	else if (str_cmp(list->arg[0], "unset"))
		return(my_unset(list_env,list->arg), 1);
	else if (str_cmp(list->arg[0], "export"))
		return(my_export(*list_env,list->arg), 1);
	else if (str_cmp(list->arg[0], "exit"))
		my_exit(list->arg);
	else if (str_cmp(list->arg[0], "echo"))
		return (my_echo(list->arg), 1);
	return(0);	
}

void	 excut_comand(t_var	*var, t_cmd *list, t_env_list **list_env)
{
	int b;
	char	*path;
	int		child;
	char	**arg;
	
	arg = NULL;
	if (var->last_in >= 0)
	{
		var->sav_in = dup(0);
		dup2(var->last_in, 0);
	}
	if (var->last_out >= 0)
	{
		var->sav_out = dup(1);
		dup2(var->last_out, 1);
	}
	b = bilt_in(list, &*list_env);
	path = list->arg[0];
	if (b == 0)
	{
		arg = return_list_to_arg(*list_env);
		if (access(list->arg[0], X_OK) < 0)
			path = it_correct_comnd(list->arg[0], *list_env);
		if (!path)
		{
			write_err("Minishell: ", list->arg[0],": command not found\n");
			exit_sta = CMD_NOTFIND;
			return ;
		}
		if (var->pipe == 1)
		{
			pipe(var->pipe_fd);
		}
		b = fork();
		if (b == 0)
		{
			exit_sta = 0;
			if (var->last_in >= 0)
				dup2(var->last_in, 0);
			if (var->last_out >= 0)
				dup2(var->last_out, 1);
			execve(path, list->arg, arg);
		}
		wait(&child);
	}
	if (var->last_in >= 0)
	{
		dup2(var->sav_in, 0);
		close (var->last_in);
	}
	if (var->sav_out >= 0)
	{
		dup2(var->sav_out, 1);
		close (var->last_out);
	}
}


void	exc(t_cmd *list, t_env_list **list_env)
{
	t_var	var;
	
	var.pipe = 0;
	if (!list->next)
	{
		rederection(list, &var);
		if (var.last_in == ERORR || var.last_out == ERORR)
			return;
		excut_comand(&var, list, &*list_env);
		return ;
	}
	var.pipe = 1;
	while (list->next)
	{
		rederection(list, &var);
		if (var.last_in == ERORR || var.last_out == ERORR)
			return;
		excut_comand(&var, list, &*list_env);
		list = list->next;
	}
}
