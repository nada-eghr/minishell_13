/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:27:48 by naessgui          #+#    #+#             */
/*   Updated: 2025/08/10 17:42:55 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*start_pars(t_vmin *v, t_var *var, int *continu, t_env_list *env_list)
{
	t_token	*tokens;
	char	*input;

	v->cont = 0;
	input = readline("minishell$ ");
	input_check(input, env_list, var);
	if (is_line_empty(input))
		return (*continu = 1, free(input), NULL);
	add_history(input);
	if (check_quotes(input, &*var))
		return (*continu = 1, free(input), NULL);
	tokens = convert_to_node(input);
	if (!tokens)
		return (*continu = 1, free(tokens), NULL);
	free(input);
	return (expand_token(tokens, env_list, &var->exit_stat));
}

void	first_step(char **env, t_vmin *v)
{
	g_sigg = NO_SIG_NAL;
	if (!env[0])
		defult_env(&v->env_list);
	else
		v->env_list = get_list_env(env);
	rl_catch_signals = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handler);
	g_sigg = NO_SIG_NAL;
	v->var.exit_stat = 0;
}

int	main(int ac, char **av, char **env)
{
	t_vmin	v;

	(void)ac;
	(void)av;
	first_step(env, &v);
	while (1)
	{
		v.filter_lst = start_pars(&v, &v.var, &v.cont, v.env_list);
		if (!v.filter_lst && v.cont == 1)
			continue ;
		v.second_tokens = second_tokinization(v.filter_lst);
		free_list(v.filter_lst);
		v.second_tokens_head = v.second_tokens;
		remove_empty_node(&v.second_tokens);
		if (check_error(&v.second_tokens, &v.var) == 1)
		{
			free_second_tokens(&v.second_tokens_head);
			continue ;
		}
		v.cmd = list_cmd(v.second_tokens);
		exc(v.cmd, &v.env_list, &v.var);
		free_list1(v.second_tokens);
		free_cmd_list(&v);
	}
	return (0);
}
