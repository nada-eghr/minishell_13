// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   main.c                                             :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/05/19 16:27:48 by naessgui          #+#    #+#             */
// /*   Updated: 2025/07/29 11:14:23 by naessgui         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */


// #include "minishell.h"

// int sigg = 0;

// bool	is_space(char c)
// {
// 	return (c == ' ' || c == '\t');
// }

// // bool	is_line_empty(const char *line)
// // {
// // 	int	i;

// // 	if (!line)
// // 		return (true);
// // 	i = 0;
// // 	while (line[i])
// // 	{
// // 		if (!is_space(line[i]))
// // 			return (false);
// // 		i++;
// // 	}
// // 	return (true);
// // }
// void	handler(int s)
// {
// 	(void)s;
		
// 	//printf("coco\n");
// 	write(1, "\n", 1);
// 	rl_replace_line("", 0);
// 	rl_on_new_line();
// 	rl_redisplay(); 
// }
// void signal_handel(int *exit)
// {

// 	signal(SIGQUIT, SIG_IGN);
// 	signal (SIGINT, handler);
// 	*exit = 0;
// }

// void	defult_env(t_env_list **env)
// {
// 	char *pwd;
// 	int i;
	
// 	i = 0;
// 	pwd = getcwd(NULL, 0);
// 	*env = ft_lstnew_env(ft_strjoin("PATH=", pwd));
// 	free(pwd);
// 	ft_lstadd_back(&*env,ft_lstnew_env(ft_strjoin("SHLVL=", "1")));
// 	ft_lstadd_back(&*env,ft_lstnew_env(ft_strjoin("_=", "/usr/bin/env")));
// 	ft_lstadd_back(&*env,ft_lstnew_env(ft_strjoin("OLDPWD", NULL)));
// }
// int	main(int ac , char **av, char **env)
// {
// 	(void)ac;
// 	(void)av;
// 	t_env_list	*env_list;
// 	t_var		var;
// 	char	*input;
	
// 	if (!env[0])
// 		defult_env(&env_list);
// 	else
// 		env_list = get_list_env(env);
// 	rl_catch_signals = 0;
// 	signal_handel(&var.exit_stat);
// 	while (1)
// 	{
// 		input = readline("minishell$ ");
// 		if (!input)
// 		{
// 			write(1, "exit\n", 5);
// 			exit (0);
// 		}
// 		if (is_line_empty(input))
// 		{
// 			free(input);
// 			continue;
// 		}
// 		add_history(input);
// 		if(check_quotes(input , &var))
// 		{
// 			free(input);
// 			continue;
// 		}
// 		t_token *tokens = convert_to_node(input);
// 		// while(tokens)
// 		// {
// 		// 	printf("%s\n",tokens->token);
// 		// 	tokens = tokens->next;
// 		// }
// 		t_token *filter_lst= expand_token(tokens , env_list, &var.exit_stat);
// 		t_second_token *second_tokens = second_tokinization(filter_lst);

// 		if (!tokens)
// 		{
// 			free(tokens);
// 			continue;
// 		}
// 		if (check_error(&second_tokens , &var) == 1)
// 		{
// 			free_list1(second_tokens);
// 			continue;
// 		}
// 		// t_token *toke = convert_to_token(filter_lst);// u need to work with this linked list in herdoc
// 		t_cmd *cmd = list_cmd(second_tokens);
// 		exc(cmd, &env_list, &var);
// 		// print_cmd(cmd);
// 		filter_lst = NULL;
// 	}
// 	return (0);
// }
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:27:48 by naessgui          #+#    #+#             */
/*   Updated: 2025/07/26 21:14:51 by naessgui         ###   ########.fr       */
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
	(void)ac;
	(void)av;
	t_env_list	*env_list;
	t_var		var;
	char	*input;
	
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
		//filter_lst = NULL;
	}
	return (0);
}

