/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slamhaou <slamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 17:38:08 by slamhaou          #+#    #+#             */
/*   Updated: 2025/07/04 12:30:05 by slamhaou         ###   ########.fr       */
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
	if (!list->arg[0])
		return (1);
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
int	first(t_var	*var, char c)
{
	
	if (c == 'f')
	{
		//close (var->pipe_fd[0]);
		dup2(var->pipe_fd[1], 1);
		dup2(var->pipe_fd[0], 0);
	}
	else if (c == 'n')
	{
		dup2(var->pipe_fd[0], 0);
		dup2(var->pipe_fd[1], 1);
	}
	else if (c == 'l')
	{
		if (var->sav_rd_fd >= 0)
			dup2(var->sav_rd_fd, 0);
		else
		{
			dup2(var->pipe_fd[0], 0);
			dup2(var->sav_rd_fd, 0);
		}
	}
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
	return (1);
}
void	 excut_comand(t_var	*var, t_cmd *list, t_env_list **list_env, char c)
{
	int b;
	char	*path;
	int		child;
	char	**arg;
	
	arg = NULL;
	path = NULL;

	if (first(var, c) < 0)
		return ;
	b = bilt_in(list, &*list_env);
	if (b == 0) // if cmd not builtin
	{
		arg = return_list_to_arg(*list_env); // convert t_env to char **
		if (access(list->arg[0], X_OK) < 0)
			path = it_correct_comnd(list->arg[0], *list_env);
		if (!path)
		{
			write_err("Minishell: ", list->arg[0],": command not found\n");
			exit_sta = CMD_NOTFIND;
			return ;
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
		var->sav_rd_fd = var->sav_rd_fd;
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
	var.sav_rd_fd = 0;
	if (!list->next)
	{
		rederection(list, &var);
		if (var.last_in == ERORR || var.last_out == ERORR)
			return;
		excut_comand(&var, list, &*list_env, '\0');
		return ;
	}
	var.pipe = 2;
	excut_comand(&var, list, &*list_env, 'f');
	list = list->next;
	var.pipe = 1;
	while (list->next)
	{
		rederection(list, &var);
		if (var.last_in == ERORR || var.last_out == ERORR)
			return;
		excut_comand(&var, list, &*list_env, 'n');
		list = list->next;
	}
	if (list->next)
	{
		var.pipe = 3;// aker command btkteb bel stdout
		excut_comand(&var, list, &*list_env, 'l');
	}
}
