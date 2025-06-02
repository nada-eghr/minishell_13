/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ignor_fun_now.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slamhaou <slamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:42:51 by slamhaou          #+#    #+#             */
/*   Updated: 2025/05/22 10:43:04 by slamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heder_shell.h"

char	**return_list_to_arg(t_env_list *list_env)
{
	char	**arg;
	int		i;
	int		j;
	int		k;
	int		s;
	t_env_list *l;
	
	i = 0;
	j = 0;
	k = 0;
	s = 0;
	l = list_env;
	while (l)
	{
		i++;
		l = l->next;
	}
	l = list_env;
	arg = malloc(sizeof(char *) * (i + 1));
	while (j < i)
	{
		arg[j] = malloc(ft_strlen(list_env->content.first) + ft_strlen(list_env->content.last) + 2);
		while (list_env->content.first[k])
		{
			arg[j][k] = list_env->content.first[k];
			k++;
		}
		arg[j][k++] = '=';
		while (list_env->content.last[s])
			arg[j][k++] = list_env->content.last[s++];
		arg[j][k] = '\0';
		j++;
		list_env = list_env->next;
		k = 0;
		s = 0;
	}
	arg[j] = NULL;
	return (arg);
}