/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slamhaou <slamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:44:00 by slamhaou          #+#    #+#             */
/*   Updated: 2025/07/07 14:20:11 by slamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	my_pwd(int *exit_sta)
{
	char *path;

	path = getcwd(NULL, 1);
	if (!path)
		return ;
	printf("%s\n", path);
	free(path);
	*exit_sta = 0;
}	