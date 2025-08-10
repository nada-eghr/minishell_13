/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:20:29 by slamhaou          #+#    #+#             */
/*   Updated: 2025/08/10 12:28:56 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	chake_args(char *str, int *pls)
{
	int	i;

	i = 0;
	if ((str[i] <= '9' && str[i] >= '0') || (is_alpha(str[i]) == 0))
		if (str[i] != '_')
			return (1);
	while (str[i] && str[i] != '=')
	{
		if (is_alpha(str[i]) == 0)
		{
			if (str[i] != '=' && str[i] != '_' && str[i] != '+' 
				&& ft_isdigit(str[i]) == 0)
				return (1);
		}
		if (str[i] == '+' && is_alpha(str[i - 1]) && str[i + 1] == '=')
			*pls = 1;
		if (str[i] == '+' && str[i + 1] != '=')
			return (1);
		i++;
	}
	if (str[i] && str[i] == '=')
		if (serch(str, '!'))
			return (1);
	return (0);
}

void	organized_nod(t_env_list *env, char *arg, int j)
{
	char	*st;
	int		i;

	i = 0;
	free(env->content.value);
	env->content.value = NULL;
	arg[j++] = '=';
	st = malloc(ft_strlen(&arg[j]) + 1);
	if (!st)
		return ;
	while (arg[j])
		st[i++] = arg[j++];
	st[i] = '\0';
	env->content.value = st;
}

int	orredy_hav_valu(t_env_list *env, char *arg)
{
	int		sv_ind;

	sv_ind = serch_equal(arg);
	while (env)
	{
		if (str_cmp(arg, env->content.key))
		{
			if (sv_ind < 0)
				return (1);
			organized_nod(env, arg, sv_ind);
			return (1);
		}
		env = env->next;
	}
	if (sv_ind > 0)
		if (!arg[sv_ind])
			arg[sv_ind] = '=';
	return (0);
}

void	have_pls_(t_env_list *env, char *arg)
{
	int		i;
	char	*join;

	i = 0;
	while (arg[i] && arg[i] != '+')
		i++;
	if (arg[i] == '+')
	{
		arg[i] = '\0';
		while (env && !str_cmp(env->content.key, arg))
			env = env->next;
		if (env)
		{
			join = ft_strjoin(env->content.value, &arg[i + 2], N_FREE);
			free(env->content.value);
			env->content.value = join;
		}
	}
}

void	my_export(t_env_list *env, char **args, int *exit_st)
{
	int	i;
	int	pls;

	i = 1; 
	pls = 0;
	if (args[i] == NULL)
		print_all_var(env, exit_st);
	while (args[i])
	{
		if (chake_args(args[i], &pls))
		{
			write_err("Minishell: export: `", args[i],
				"': not a valid identifier\n");
			*exit_st = 1;
			return ;
		}
		if (pls == 1)
			have_pls_(env, args[i]);
		else if (orredy_hav_valu(env, args[i]) == 0)
			ft_lstadd_back(&env, ft_lstnew_env(args[i], ENV));
		i++;
	}
	*exit_st = 0;
}
