/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:27:48 by naessgui          #+#    #+#             */
/*   Updated: 2025/08/04 13:13:44 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int sigg = 0;

bool	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

void	handler(int s)
{
	(void)s;
	sigg = 1;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay(); 
	return;
}

void	defult_env(t_env_list **env)
{
	char *pwd;
	int i;
	
	i = 0;
	pwd = getcwd(NULL, 0);
	*env = ft_lstnew_env(ft_strjoin("PATH=", pwd));
	free(pwd);
	ft_lstadd_back(&*env,ft_lstnew_env(ft_strjoin("SHLVL=", "1")));
	ft_lstadd_back(&*env,ft_lstnew_env(ft_strjoin("_=", "/usr/bin/env")));
	ft_lstadd_back(&*env,ft_lstnew_env(ft_strjoin("OLDPWD", NULL)));
}
int	main(int ac , char **av, char **env)
{
	t_env_list	*env_list;
	t_var		var;
	char*input;

	(void)ac;
	(void)av;
	sigg = NO_SIG_NAL;
	var.exit_stat = 0;
	if (!env[0])
		defult_env(&env_list);
	else
		env_list = get_list_env(env);
	rl_catch_signals = 0;
	signal(SIGQUIT, SIG_IGN);
	signal (SIGINT, handler);
	while (1)
	{
		input = readline("minishell$ ");
		if (sigg !=  NO_SIG_NAL)
		{
			var.exit_stat = sigg;
			sigg = NO_SIG_NAL;
		}
		if (!input)
		{
			write(1, "exit\n", 5);
			exit (0);
		}
		if (is_line_empty(input))
		{
			free(input);
			continue;
		}
		add_history(input);
		if(check_quotes(input, &var))
		{
			free(input);
			continue;
		}
		t_token *tokens = convert_to_node(input);
		t_token *filter_lst= expand_token(tokens , env_list, &var.exit_stat);
		t_second_token *second_tokens = second_tokinization(filter_lst);
		  remove_empty_node(&second_tokens);
		if (!tokens)
		{
			free(tokens);
			continue;
		}
		if (check_error(&second_tokens , &var) == 1)
		{
			free_list1(second_tokens);
			continue;
		}
		t_cmd *cmd = list_cmd(second_tokens);
		exc(cmd, &env_list, &var);
	}
	return (0);
}

