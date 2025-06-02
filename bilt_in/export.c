/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slamhaou <slamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:20:29 by slamhaou          #+#    #+#             */
/*   Updated: 2025/05/30 08:10:20 by slamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heder_shell.h"

int	is_alpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}
int	chake_args(char *str)
{
	int	i;

	i = 0;
	if ((str[i] <= '9' && str[i] >= '0') || (is_alpha(str[i]) == 0))
		if (str[i] != '_')
		return (1);
	while (str[i])
	{
		if (!(str[i] >= 'a' && str[i] <= 'z') && !(str[i] >= 'A' && str[i] <= 'Z'))
			if (str[i] != '=' && str[i] != '_')
				return (1);
		i++;
	}
	return (0);
}

void	print_all_var(t_env_list *env)
{
	while (env)
	{
		if (str_cmp(env->content.first, "_") == 0)
		{
			if (env->content.last)
				printf("declare -x %s=\"%s\"\n", env->content.first, env->content.last);
			else
				printf("declare -x %s\n", env->content.first);
		}
		env = env->next;
	}
}
int	orredy_hav_valu(t_env_list *env, char *arg)
{
	int	i;
	int	j;
	char	*st;
	
	i = 0;
	j = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	st = malloc(i + 1);
	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		st[i] = arg[i];
		i++;
	}
	st[i] = '\0';
	while (env)
	{
		if (str_cmp(st, env->content.first))
		{
			free(st);
			free(env->content.last);
			if (arg[i] == '=')
				i++;
			st = malloc(ft_strlen(&arg[i]) + 1);
			while (arg[i])
				st[j++] = arg[i++];
			st[j] = '\0';
			env->content.last = st;
			st = NULL;
			return (1);
		}
		env = env->next;
	}
	return (0);
}

int	my_export(t_env_list *env, char **args)
{
	int	i;
	int ret;

	i = 1;  
	ret = 0;
	if (args[i] == NULL)
		print_all_var(env);
	while (args[i])
	{
		if (chake_args(args[i]))
		{
			write_erorr("Minishell: export: ", args[i]);
			write_erorr("not a balid identifier\n", NULL);
			ret = 1;
		}
		else if (orredy_hav_valu(env, args[i]) == 0)
				ft_lstadd_back(&env,ft_lstnew(args[i]));
		i++;
	}
	return (0);
}
