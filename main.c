/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slamhaou <slamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:27:48 by naessgui          #+#    #+#             */
/*   Updated: 2025/07/03 22:17:16 by slamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>

int	main(int ac , char **av, char **env)
{
	(void)ac;
	(void)av;
	t_env_list *env_list;
	env_list = get_list_env(env);
	while (1)
	{
		
		char *input = readline("minishell$ ");
		add_history(input);
		t_token *tokens = convert_to_node(input);
		t_token *filter_lst= expand_token(tokens , env_list);
		if (!tokens)
		{
			free(tokens);
			continue;
		}
		if (check_error(&tokens) == 1)
		{
			// printf("minishell : syntax error"); /*free*/
			free_list(tokens);
			continue;
		}
		t_cmd *cmd = list_cmd(filter_lst);
		exc(cmd, &env_list);
		//print_cmd(cmd);
		// filter_lst = NULL;/
	
	}
	return (0);
}
