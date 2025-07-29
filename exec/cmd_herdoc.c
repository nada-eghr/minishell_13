/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_herdoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 16:20:17 by slamhaou          #+#    #+#             */
/*   Updated: 2025/07/29 10:57:12 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	serch_del(char *str, char *del)
{
	int i;
	int	j;
	int len;

	if (!str)
		return (0);
	i = 0;
	len =  ft_strlen(del);
	while (i < len)
	{
		j = 0;
		while (str[i] && del[j] && str[i] == del[j])
		{
			i++;
			j++;
		}
		if (!del[j] && str[i] == '\n' && !str[i + 1])
			return (1);
		i = i - j;
		i++;
	}
	return (0);
}

char *expand_herdoc(char *input, t_env_list *env)
{
	t_token	tok;
	int exits;
	
	exits = 0;
	tok.token = input;
	tok.type = 0;
	tok.next = NULL;
	tok.is_quoted = NULL;
	expand_double_quote(&tok,env, &exits);
	return (tok.token);
}

void	herdk(int s)
{
	(void)s;
	sigg = 4;
	write(1, "\n", 1);
	exit (1);
}


void	creat_child_herdoc(char **arr_hrd, t_var *var, t_env_list *env)
{
	int	herdoc[2];
	int	i;
	int j;
	int inform;
	char *input;

	//(void)env;
	i = 0;
	j = 0;
	input = NULL;
	pipe(herdoc);
	while (arr_hrd[j])
		j++;
	signal(SIGINT, SIG_IGN);
	int id = fork();
	if (id == 0)
	{
		signal(SIGINT, herdk);
		close (herdoc[0]);
		while (i < j - 1)
		{
			while (serch_del(input, arr_hrd[i]) == 0)
			{
				write(1, "> ", 2);
				input = get_next_line(0);
				if (!input)
					break;
				free(input);
			}
			i++;
		}
		while (1)
		{
			write(1, "> ", 2);
			input = get_next_line(0);
			if (!input || serch_del(input, arr_hrd[j - 1]) == 1)
			{
				if (!input)
					write(1, "\n", 1);
				if (input)
					free(input);
				exit(0);
			}
			input = expand_herdoc(input, env);
			write(herdoc[1], input, ft_strlen(input));
			free(input);
		}
	}
	waitpid(id, &inform, 0);
	close (herdoc[1]);
	int exit_code = WEXITSTATUS(inform);
	if (exit_code)
	{
		close (herdoc[0]);
		var->her_s = 1;
	}
	var->last_in = herdoc[0];
	signal_handel(&var->exit_stat);
}
int	open_herdok(t_redirection *red, t_var *var, t_env_list *env)
{
	int her;
	char **arr;
	t_redirection *r;

	r = red;
	her = 0;
	while (red)
	{
		if (red->type == T_HEREDOC)
			her++;
		red = red->next;	
	}
	arr = malloc(sizeof(char *) * (her + 1));
	her = 0;
	while (r)
	{
		if (r->type == T_HEREDOC)
			arr[her++] = r->file;
		r = r->next;
	}
	arr[her] = NULL;
	creat_child_herdoc(arr, var, env);
	return (var->last_in);
}
