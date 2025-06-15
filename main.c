/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:27:48 by naessgui          #+#    #+#             */
/*   Updated: 2025/06/15 17:17:55 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*input;
	t_token	*tokens;
	t_cmd	*cmd;
	t_token	*current;
	// atexit(ll);
	while (1)
	{
		input = readline("minishell$");
		tokens = convert_to_node(input);
		if (!tokens)
		{
			free(tokens);
			return (0);
		}
		if (check_error(&tokens) == 1)
		{
			// printf("minishell : syntax error"); /*free*/
			free_list(tokens);
			return (0);
		}
		cmd = list_cmd(tokens);
		print_cmd(cmd);
		if (!tokens)
		{
			free(tokens);
			return (0);
		}
		if (check_error(&tokens) == 1)
		{
			// printf("minishell : syntax error"); /*free*/
			free_list(tokens);
			exit(1);
			return (0);
		}
		// t_cmd *cmd = convert_to_cmd(&tokens)
		current = tokens;
		while (current)
		{
			printf("{token -> %s } ", current->token);
			printf("{type -> %d } ", current->type);
			current = current->next;
		}
		printf("\n");
		printlinkedlist(tokens);
		// Free memory if needed
		free_list(tokens);
	}
	return (0);
}
