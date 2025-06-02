/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slamhaou <slamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 10:11:49 by slamhaou          #+#    #+#             */
/*   Updated: 2025/05/24 17:44:09 by slamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heder_shell.h"


void	update_od_nw_pwd(t_env_list *env, char *s)
{
		while (str_cmp(env->content.first, s) == 0)
			env = env->next;
		if (str_cmp(env->content.first, s))
		{
			free(env->content.last);
			env->content.last = getcwd(NULL, 0);
		}
}

int	my_cd(t_env_list *env, char **arg) 
{
	char *path;
	int err;

	update_od_nw_pwd(env, "OLDPWD");
	if (str_cmp(arg[0], "cd") && arg[1] == NULL)
	{
		path = my_get_env("HOME", env);
		if (!path)
		{
		 	write (2, "Minishell: cd: HOME not set\n", 24);
			return (1);
		}
		err = chdir(path);
		if (err != 0)
			return (perror("cd"), 1);
		return (0);
	}
	err = chdir(arg[1]);
	update_od_nw_pwd(env, "PWD");
	if (err != 0)
	{
		write(2,"Minishell: cd: ", 15);
		write(2, arg[1], ft_strlen(arg[1]));
		write(2, ": ", 2);
		return (perror(NULL), 1);
	}
	return (0);
}
