/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slamhaou <slamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:00:50 by slamhaou          #+#    #+#             */
/*   Updated: 2025/05/30 10:09:45 by slamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heder_shell.h"

int	my_env(t_env_list *env)
{
	while (env)
	{
		if (env->content.last)
			printf("%s=%s\n", env->content.first, env->content.last);
		env = env->next;
	}
	return (0);
}