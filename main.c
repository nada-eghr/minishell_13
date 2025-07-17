/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slamhaou <slamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:27:48 by naessgui          #+#    #+#             */
/*   Updated: 2025/07/17 18:53:50 by slamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int sigg = 0;

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
void	handler(int s)
{
	if (s == SIGINT)
	{
		sigg = 1;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay(); 
		return;
	}
}
void signal_handel(int *exit)
{

	signal(SIGQUIT, SIG_IGN);
	signal (SIGINT, handler);
	*exit = 0;
}

int	main(int ac , char **av, char **env)
{
	(void)ac;
	(void)av;
	char *input;
	t_env_list	*env_list;
	t_var		var;

	rl_catch_signals = 0;
	signal_handel(&var.exit_stat);
	env_list = get_list_env(env);
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			write(1, "exit\n", 5);
			break;
		}
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
		if (!s || is_line_empty(s))
		{
			free(s);
			free_list(tokens);
			continue;
		}
		t_token *toke = convert_to_token(s);
		if (check_error1(&toke) == 1)
		{
			free_list(tokens);
			continue;
		}
		t_cmd *cmd = list_cmd(toke);
		exc(cmd, &env_list, &var);
		//print_cmd(cmd);
		filter_lst = NULL;
	}
	return (0);
}
