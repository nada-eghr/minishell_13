/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slamhaou <slamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 17:38:08 by slamhaou          #+#    #+#             */
/*   Updated: 2025/06/05 13:24:17 by slamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heder_shell.h"

int	exit_sta = 0;

char	*my_get_env(char *str, t_env_list *env)
{

	while (env)
	{
		if (str_cmp(str, env->content.first))
			return (env->content.last);
		env = env->next;	
	}
	return (NULL);
}
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
int		bilt_in(t_my_list *list, t_env_list **list_env)
{
	if (str_cmp(list->args[0], "pwd")|| str_cmp(list->args[0], "PWD"))
		return(my_pwd(), 1);
	else if (str_cmp(list->args[0], "env"))
		return (my_env(*list_env), 1);
	else if (str_cmp(list->args[0], "cd"))
		return(my_cd(*list_env,list->args), 1);
	else if (str_cmp(list->args[0], "unset"))
		return(my_unset(list_env,list->args), 1);
	else if (str_cmp(list->args[0], "export"))
		return(my_export(*list_env,list->args), 1);
	else if (str_cmp(list->args[0], "exit"))
		my_exit(list->args);
	else if (str_cmp(list->args[0], "echo"))
		return (my_echo(list->args), 1);
	return(0);	
}

void	excut_comand(t_my_list *list, t_env_list **list_env)
{
	int b;
	char	*path;
	int		child;
	char	**arg;
	
	arg = NULL;
	//int status;
	b = bilt_in(list, &*list_env);
	if (b == 0)
	{
		arg = return_list_to_arg(*list_env);
		path = it_correct_comnd(list->args[0], *list_env);
		if (!path)
		{
			write_err("Minishell: ", list->args[0],": command not found\n", '\0');
			exit_sta = CMD_NOTFIND;
			return ;
		}
		b = fork();
		if (b == 0)
			execve(path, list->args, arg);
		wait(&child);
	}
}

void	exc(t_my_list *list, t_env_list **list_env)
{
	
	if (!list->next)
		excut_comand(list, &*list_env);
	// while(list->next)
	// {
	// 	excut_comand(list, &*list_env);
	// 	list = list->next;
	// }
}
