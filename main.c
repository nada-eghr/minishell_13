/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:27:48 by naessgui          #+#    #+#             */
/*   Updated: 2025/07/10 13:29:41 by naessgui         ###   ########.fr       */
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
		if(check_quotes(input))
		{
			free(input);
			continue;
		}
	
		t_token *tokens = convert_to_node(input);
		
		t_token *filter_lst= expand_token(tokens , env_list);
		if (!tokens)
		{
			free(tokens);
			continue;
		}
		if (check_error(&tokens) == 1)
		{
			free_list(tokens);
			continue;
		}
		char *s=  filter_token(filter_lst);
		t_token *toke = convert_to_token(s);
		t_token *c = toke;
		printlinkedlist(c);
		if (check_error1(&toke) == 1)
		{
			free_list(tokens);
			continue;
		}
		
		
		printf("\n");
		t_cmd *cmd = list_cmd(toke);
		print_cmd(cmd);
		exc(cmd, &env_list);
		filter_lst = NULL;
		
	
	}
	return (0);
}

