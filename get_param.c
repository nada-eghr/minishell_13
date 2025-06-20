/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_param.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:56:54 by naessgui          #+#    #+#             */
/*   Updated: 2025/06/18 17:43:30 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	**get_args(t_token *token)
{
	t_token	*tmp;
	t_token	*prev;
	int		i;
	char	**cmd;

	tmp = token;
	i = 0;
	cmd = malloc(sizeof(char *) * (count_args(token) + 1));
	if (!*cmd)
		return (NULL);
	if (tmp->type == TOKEN_WORD || tmp->type == TOKEN_S_QUOTE || tmp->type == TOKEN_D_QUOTE)
		cmd[i++] = ft_strdup(tmp->token);
	prev = tmp;
	tmp = tmp->next;
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