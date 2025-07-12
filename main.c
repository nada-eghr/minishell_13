/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:27:48 by naessgui          #+#    #+#             */
/*   Updated: 2025/07/12 16:14:12 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
#include <readline/readline.h>



bool	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

bool	is_line_empty(const char *line)
{
	int	i;

	if (!line)
		return (true);
	i = 0;
	while (line[i])
	{
		if (!is_space(line[i]))
			return (false);
		i++;
	}
	return (true);
}

int	main(int ac , char **av, char **env)
{
	(void)ac;
	(void)av;
	t_env_list *env_list;
	env_list = get_list_env(env);

	t_var var;
	
	while (1)
	{
		char *input = readline("minishell$ ");
		if (!input || is_line_empty(input))
		{
			free(input);
			continue;
		}
		add_history(input);
		if(check_quotes(input))
		{
			free(input);
			continue;
		}
		t_token *tokens = convert_to_node(input);
		t_token *filter_lst= expand_token(tokens , env_list, &var.exit_stat);
		t_second_token *second_tokens = second_tokinization(filter_lst);
		if (!tokens)
		{
			free(tokens);
			continue;
		}
		if (check_error(&second_tokens) == 1)
		{
			free_list1(second_tokens);
			continue;
		}
		// t_token *toke = convert_to_token(filter_lst);// u need to work with this linked list in herdoc
		t_cmd *cmd = list_cmd(second_tokens);
		exc(cmd, &env_list);
		filter_lst = NULL;
	}
	return (0);
}
