/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slamhaou <slamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 17:09:48 by slamhaou          #+#    #+#             */
/*   Updated: 2025/08/09 17:20:34 by slamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		g_sigg = 0;

void	handler(int s)
{
	(void)s;
	g_sigg = 1;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	return ;
}

void	defult_env(t_env_list **env)
{
	char	*pwd;
	int		i;

	i = 0;
	pwd = getcwd(NULL, 0);
	*env = ft_lstnew_env(ft_strjoin("PWD=", pwd), ENV_DEFAULT);
	free(pwd);
	ft_lstadd_back(&*env, ft_lstnew_env
		(ft_strjoin("SHLVL=", "1"), ENV_DEFAULT));
	ft_lstadd_back(&*env, ft_lstnew_env
		(ft_strjoin("_=", "/usr/bin/env"), ENV_DEFAULT));
	ft_lstadd_back(&*env, ft_lstnew_env
		(ft_strjoin("OLDPWD", NULL), ENV_DEFAULT));
}

void	input_chack(char *input, t_env_list *env_list, t_var *var)
{
	if (g_sigg != NO_SIG_NAL)
	{
		var->exit_stat = g_sigg;
		g_sigg = NO_SIG_NAL;
	}
	if (!input)
	{
		write(1, "exit\n", 5);
		free_env(env_list);
		exit (var->exit_stat);
	}
}
