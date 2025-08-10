/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 13:16:20 by slamhaou          #+#    #+#             */
/*   Updated: 2025/08/10 16:00:40 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handler_sig_herd(int s)
{
	(void)s;
	write(1, "\n", 1);
	exit(130);
}

char	*expand_herdoc(char *input, t_env_list *env)
{
	t_token	tok;
	int		exits;

	exits = 0;
	tok.token = input;
	tok.type = 0;
	tok.next = NULL;
	tok.is_quoted = NULL;
	expand_word_token(&tok, env, &exits);
	input = NULL;
	return (tok.token);
}

void	wait_heredoc(int *herdoc, t_var *var, int id)
{
	int	inform;

	close (herdoc[1]);
	waitpid(id, &inform, 0);
	if (WEXITSTATUS(inform) == OUT_SIG_INT)
	{
		close(herdoc[0]);
		var->her_s = 1;
		var->exit_stat = 130;
	}
	else
		var->exit_stat = 0;
	var->last_in = herdoc[0];
}

int	serch_del(char *str, char *del)
{
	int	i;
	int	j;

	if (!str)
		return (0);
	i = 0;
	j = 0;
	while (str[j] && del[i] && str[i] == del[j])
	{
		i++;
		j++;
	}
	if (!del[j] && str[i] == '\n' && !str[i + 1])
		return (1);
	return (0);
}
