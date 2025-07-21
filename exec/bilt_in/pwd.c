/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slamhaou <slamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:44:00 by slamhaou          #+#    #+#             */
/*   Updated: 2025/07/20 11:57:02 by slamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	my_pwd(int *exit_sta)
{
	char *path;

	path = getcwd(NULL, 1);
	if (!path)
		return ;
	write(1, path, ft_strlen(path));
	write(1, "\n", 1);
	free(path);
	*exit_sta = 0;
}	