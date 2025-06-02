/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slamhaou <slamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 20:21:37 by slamhaou          #+#    #+#             */
/*   Updated: 2025/06/02 12:31:23 by slamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heder_shell.h"

void	write_err(char *s, char *arg, char *last, char up)
{
	write(2, s, ft_strlen(s));
	if (up && arg)
	{
		write(2, &up, 1);
		write(2, arg, ft_strlen(arg));
		write(2, &up, 1);
	}
	else if (arg)
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
			return((int)n);
		}
		i++;
	}
	return ((int)n);
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

void	alon_exit(void)
{
	write(2, "exit\n", 6);
	exit(exit_sta);
}
void	my_exit(char **args)
{
	int	num;
	int	eror;

	eror = 1;
	if (args[1] == NULL)
		alon_exit();
	if (another_alpha(args[1]))
	{
		write_err("exit\nMinishell: exit: ", args[1],
		 ": numeric argument required\n", '\0');
		exit (255);
	}
	if	(args[2] != NULL)
	{
		write_err("exit\nMinishell:exit: ", NULL,
		"too many arguments\n",'\0');
		exit_sta = 1;
		return ;
	}
	num = ft_atoi(args[1], &eror);
	if (eror == -1)
		write_err("exit\nMinishell: exit: ", args[1], 
		": numeric argument required\n", '\0');
	exit (num);
}
