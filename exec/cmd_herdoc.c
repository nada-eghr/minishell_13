/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_herdoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slamhaou <slamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 16:20:17 by slamhaou          #+#    #+#             */
/*   Updated: 2025/07/21 14:44:14 by slamhaou         ###   ########.fr       */
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
		if (!del[j] && !str[i])
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

void	creat_child_herdoc(char **arr_hrd, t_var *var, t_env_list *env)
{
	int	herdoc[2];
	int id;
	int st;
	int	i;
	int j;
	char *input;

	(void)env;
	i = 0;
	j = 0;
	input = NULL;
	pipe(herdoc);
	while (arr_hrd[j])
		j++;
	id = fork();
	if (id == 0)
	{
		close (herdoc[0]);
		while (i < j - 1)
		{
			while (serch_del(input, arr_hrd[i]) == 0)
			{
				input = readline("> ");
				if (!input)
					break;
				free(input);
			}
			i++;
		}
		while (1)
		{
			input = readline("> ");
			if (!input || serch_del(input, arr_hrd[j - 1]) == 1)
			{
				//printf ("coco\n");
				//write(1, "halo\n", 5);
				break;
			}
			//input = expand_herdoc(input, env);
			write(herdoc[1], input, ft_strlen(input));
			write(herdoc[1], "\n", 1);
			free(input);
		}
		close(herdoc[1]);
		exit(0);
	}
	close (herdoc[1]);
	var->last_in = herdoc[0];
	waitpid(id,&st, 0);
}

void	open_herdok(t_redirection *red, t_var *var, t_env_list *env)
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
}