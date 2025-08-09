/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 12:47:58 by naessgui          #+#    #+#             */
/*   Updated: 2025/08/09 13:13:41 by naessgui         ###   ########.fr       */
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
	*env = ft_lstnew_env(ft_strjoin("PATH=", pwd));
	free(pwd);
	ft_lstadd_back(&*env, ft_lstnew_env(ft_strjoin("SHLVL=", "1")));
	ft_lstadd_back(&*env, ft_lstnew_env(ft_strjoin("_=", "/usr/bin/env")));
	ft_lstadd_back(&*env, ft_lstnew_env(ft_strjoin("OLDPWD", NULL)));
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
		exit(var->exit_stat);
	}
}
