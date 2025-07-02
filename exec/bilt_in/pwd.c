/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slamhaou <slamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:44:00 by slamhaou          #+#    #+#             */
/*   Updated: 2025/07/02 17:22:29 by slamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	my_pwd(void)
{
	char *path;

	path = getcwd(NULL, 1);
	if (!path)
		return (ERORR); 
	printf("%s\n", path);
	free(path);
	return (SUCCESS);
}	