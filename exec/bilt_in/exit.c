/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slamhaou <slamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 20:21:37 by slamhaou          #+#    #+#             */
/*   Updated: 2025/08/09 22:41:44 by slamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_atoi(char *str, int *err)
{
	unsigned long long	n;
	int					i;
	int					sin;

	i = 0;
	n = 0;
	sin = 1;
	while (str[i] <= 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sin = -1;
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		n = n * 10 + (str[i] - 48);
		if (((sin == 1) && n > LLONG_MAX)
			|| ((sin == -1) && n > (unsigned long long )LLONG_MAX + 1))
			return (*err = -1, (int)n * sin);
		i++;
	}
	return ((int)n * sin);
}

int	another_alpha(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '-' || s[i] == '+')
		i++;
	if (!s[i])
		return (1);
	while (s[i])
	{
		if (!(s[i] >= '0' && s[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

int	chake_erorr(char *args)
{
	int	eror;
	int	num;

	eror = 0;
	if (another_alpha(args))
	{
		write_err("exit\nMinishell: exit: ", args,
			": numeric argument required\n");
		exit (255);
	}
	num = ft_atoi(args, &eror);
	if (eror == -1)
	{
		write_err("exit\nMinishell: exit: ", args, 
			": numeric argument required\n");
		exit (255);
	}
	return (num);
}

int	my_exit(char **args, int *exit_st, int pip, t_env_list *env)
{
	int	num;

	if (args[1] == NULL)
	{
		if (pip == NO_PIP)
		{
			write(1, "exit\n", 6);
			free_env(env);
		}
		exit(*exit_st);
	}
	if (args[2] != NULL)
	{
		chake_erorr(args[1]);
		write_err("exit\nMinishell: exit: ", NULL,
			"too many arguments\n");
		*exit_st = 1;
		return (1);
	}
	num = chake_erorr(args[1]);
	free_env(env);
	exit (num);
}
