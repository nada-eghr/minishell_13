/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:27:48 by naessgui          #+#    #+#             */
/*   Updated: 2025/06/20 22:14:19 by naessgui         ###   ########.fr       */
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
	// atexit(ll);
	// while(env_list->next){
	// 	printf("key %s ->",env_list->content.key);
	// 	printf("value = %s \n", env_list->content.value);
	// 	env_list = env_list->next;
	// }
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
		t_cmd *cmd = list_cmd(tokens);
		print_cmd(cmd);
		
		//------------
		t_token *current = filter_lst;

		while (current)
		{
			printf("{token -> %s } ", current->token);
			printf("{type -> %d } ", current->type);
			current = current->next;
		}
		printf("\n");

		printlinkedlist(filter_lst);

		// Free memory if needed
		free_list(tokens);
	}
	return (0);
}

