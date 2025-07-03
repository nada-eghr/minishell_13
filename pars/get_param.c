/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_param.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:56:54 by naessgui          #+#    #+#             */
/*   Updated: 2025/07/01 22:01:15 by naessgui         ###   ########.fr       */
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
	if (tmp->type == T_WORD || tmp->type == T_S_QUOTE || tmp->type == T_D_QUOTE || tmp->type == T_ENV)
		count++;
	prev = tmp;
	tmp = tmp->next;
	while (tmp && tmp->type != T_PIPE)
	{
		if ((prev->type == T_PIPE || prev->type == T_WORD
				|| prev->type == T_S_QUOTE || prev->type == T_D_QUOTE
				|| prev->type == T_ENV) && (tmp->type == T_WORD
				|| tmp->type == T_D_QUOTE || tmp->type == T_S_QUOTE
				|| tmp->type == T_ENV))
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
	if (tmp->type == T_WORD || tmp->type == T_S_QUOTE || tmp->type == T_D_QUOTE
		|| tmp->type == T_ENV)
		cmd[i++] = ft_strdup(tmp->token);
	prev = tmp;
	tmp = tmp->next;
	while (tmp && tmp->type != T_PIPE)
	{
		if ((prev->type == T_PIPE || prev->type == T_WORD
				|| prev->type == T_S_QUOTE || prev->type == T_D_QUOTE
				|| prev->type == T_ENV) && (tmp->type == T_WORD
				|| tmp->type == T_D_QUOTE || tmp->type == T_S_QUOTE
				|| tmp->type == T_ENV))
			cmd[i++] = ft_strdup(tmp->token);
		prev = tmp;
		tmp = tmp->next;
	}
	return (cmd[i] = NULL , cmd);
}

// int		count;
// count = count_args(token);