/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slamhaou <slamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 17:38:08 by slamhaou          #+#    #+#             */
/*   Updated: 2025/06/19 20:40:18 by slamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heder_shell.h"

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
		new_p = str_join(split_path[i], cmd);
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

void	excut_comand(int fd, t_cmd *list, t_env_list **list_env)
{
	int b;
	char	*path;
	int		child;
	char	**arg;
	
	arg = NULL;
	b = bilt_in(list, &*list_env);
	path = list->arg[0];
	if (b == 0)
	{
		arg = return_list_to_arg(*list_env);
		if (access(list->arg[0],X_OK) < 0)
			path = it_correct_comnd(list->arg[0], *list_env);
		if (!path)
		{
			write_err("Minishell: ", list->arg[0],": command not found\n", '\0');
			exit_sta = CMD_NOTFIND;
			return ;
		}
		b = fork();
		if (b == 0)
		{
			exit_sta = 0;
			if (fd != NO_REDERCT)
				dup2(fd, 1);
			execve(path, list->arg, arg);
		}
		wait(&child);
	}
}

int	last_in(t_redirection *redi, int count_in)
{
	int	fd;
	t_redirection *p;
	
	fd = 0;
	p = redi;
	while (p)
	{
		if (p->type ==  TOKEN_REDIR_IN)
			count_in++;
		p = p->next;
	}
	while (redi)
	{
		if (redi->type == TOKEN_REDIR_IN)
		{
			fd = open(redi->file, O_RDONLY);
			if (fd < 0)
			{
				write_err("Minishell: ", redi->file, ": ", '\0');
				return (perror(NULL), -1);
			}
		}
		redi = redi->next;
	}
	return (1);
}
void how_mny_in_out_file (t_redirection *red, int *count_in, int *count_out)
{
	int	in;
	int	out;
	
	in = 0;
	out = 0;
	while (red)
	{
		if (red->type == TOKEN_REDIR_IN)
			in++;
		if ( red->type == TOKEN_REDIR_OUT 
			|| red->type == TOKEN_APPEND)
			out++;
		red = red->next;
	}
	*count_in = out;
	*count_in = in;
}
int	rederection(t_cmd *list)
{
	int fd;
	int	fd_lst_i;
	t_var	var;
	fd = 0;
	if (list->herdoc == 1)
		//open_herdok()
		fd = 0;
	how_mny_in_out_file(list->redi,&var.count_in, &var.count_out);
	fd_lst_i = last_in(list->redi, 0);
	if (fd_lst_i == -1)
		return (-1);
	//fd_lst_o = last_out();
	return (1);
}

void	exc(t_cmd *list, t_env_list **list_env)
{
	int fd;
	
	fd = 0;
	
	if (!list->next)
	{
		fd = rederection(list);
		if (fd < 0)
			return ;
		else
		{
			excut_comand(fd, list, &*list_env);
		} 
	}
}
