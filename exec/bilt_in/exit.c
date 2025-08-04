/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slamhaou <slamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 20:21:37 by slamhaou          #+#    #+#             */
/*   Updated: 2025/08/04 11:38:59 by slamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	write_err(char *s, char *arg, char *last)
{
	write(2, s, ft_strlen(s));
	 if (arg)
		write(2, arg, ft_strlen(arg));
	if (last)
		write(2, last, ft_strlen(last));
}
int	ft_atoi(char *str, int *err)
{
	int	i;
	int	sin;
	unsigned long long	n;

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
		if (((sin == 1 ) && n > LLONG_MAX ) || ((sin == -1) && n > (unsigned long long )LLONG_MAX + 1))
		{
				*err = -1;
			return((int)n * sin);
		}
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
	while (s[i])
	{
		if (!(s[i] >= '0' && s[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

void	alon_exit(int *exit_st, int pip)
{
	if (pip == NO_PIP)
		write(1, "exit\n", 6);
	exit(*exit_st);
}
void	my_exit(char **args, int *exit_st, int pip)
{
	int	num;
	int	eror;

	eror = 1;
	if (args[1] == NULL)
		alon_exit(exit_st, pip);
	if (another_alpha(args[1]))
	{
		write_err("Minishell: exit: ", args[1],
		 ": numeric argument required\n");
		exit (255);
	}
	if	(args[2] != NULL)
	{
		write_err("exit\nMinishell: exit: ", NULL,
		"too many arguments\n");
		*exit_st = 1;
		return ;
	}
	num = ft_atoi(args[1], &eror);
	if (eror == -1)
	{
		write_err("exit\nMinishell: exit: ", args[1], 
		": numeric argument required\n");
		exit (255);
	}
	exit (num);
}
