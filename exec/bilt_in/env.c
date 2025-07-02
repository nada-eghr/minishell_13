/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slamhaou <slamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:00:50 by slamhaou          #+#    #+#             */
/*   Updated: 2025/07/02 17:22:37 by slamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	my_env(t_env_list *env)
{
	while (env)
	{
		if (env->content.value)
			printf("%s=%s\n", env->content.key, env->content.value);
		env = env->next;
	}
	exit_sta = 0;
	return (0);
}