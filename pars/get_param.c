/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_param.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slamhaou <slamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:56:54 by naessgui          #+#    #+#             */
/*   Updated: 2025/07/02 17:19:44 by slamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_args(t_token *list)
{
	int		count;
	t_token	*tmp;
	t_token	*prev;

	count = 0;
	tmp = list;
	if (tmp->type == TOKEN_WORD || tmp->type == TOKEN_S_QUOTE || tmp->type == TOKEN_D_QUOTE)
		count++;
	prev = tmp;
	tmp = tmp->next;
	while (tmp && tmp->type != TOKEN_PIPE)
	{
		if ((prev->type == TOKEN_PIPE || prev->type == TOKEN_WORD
				|| prev->type == TOKEN_S_QUOTE || prev->type == TOKEN_D_QUOTE) && (tmp->type == TOKEN_WORD
				|| tmp->type == TOKEN_D_QUOTE || tmp->type == TOKEN_S_QUOTE))
			count++;
		prev = tmp;
		tmp = tmp->next;
	}
	return (count);
}

char **get_args(t_token *token)
{
	t_token *tmp = token;
	t_token *prev ;
	int i = 0;
	int count = count_args(token);
	char **cmd = malloc(sizeof(char*) * (count+2));
	if (!*cmd)
		return (NULL);
	if (tmp->type == TOKEN_WORD || tmp->type == TOKEN_S_QUOTE || tmp->type == TOKEN_D_QUOTE)
		cmd[i++] = ft_strdup(tmp->token);
	prev = tmp;
	tmp = tmp->next;
	while (tmp && tmp->type != TOKEN_PIPE)
	while (tmp && tmp->type != TOKEN_PIPE)
	{
		if ((prev->type == TOKEN_PIPE || prev->type == TOKEN_WORD
				|| prev->type == TOKEN_S_QUOTE || prev->type == TOKEN_D_QUOTE) && (tmp->type == TOKEN_WORD
				|| tmp->type == TOKEN_D_QUOTE || tmp->type == TOKEN_S_QUOTE))
			cmd[i++] = ft_strdup(tmp->token);
		prev = tmp;
		tmp = tmp->next;
	}
	cmd[i] = NULL;
	return (cmd);
}

	// int		count;
	// count = count_args(token);
	// int		count;
	// count = count_args(token);