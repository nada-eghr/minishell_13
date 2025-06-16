/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slamhaou <slamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 09:32:00 by slamhaou          #+#    #+#             */
/*   Updated: 2025/06/16 10:01:00 by slamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heder_shell.h"


int main(int ac, char **av, char **env) 
{
	char *input;
	t_cmd *cmd_list;
	t_env_list *e;
	int i;

	i = 0;
	ac = 0;
	av = NULL;
	e = get_list_env(env);
	input = "wee";
	while (input) 
	{
		input = readline("Minishell$ ");
		cmd_list = smal_list(input);
		exc(cmd_list, &e);
	}
	return 0;
}