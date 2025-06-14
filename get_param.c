/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_param.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:56:54 by naessgui          #+#    #+#             */
/*   Updated: 2025/06/14 16:34:02 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

// cmd->args = get_argsetre(t_token);

int count_args(t_token *list)
{
	int count = 0;
	t_token *tmp = list;
	t_token *prev ;
	

	if(tmp->type == TOKEN_WORD || tmp->type == TOKEN_QUOTED)
		count++;
	prev = tmp;
	tmp = tmp->next;
	while (tmp && tmp->type != TOKEN_PIPE) 
	{
		if (( prev->type == TOKEN_PIPE || prev->type == TOKEN_WORD  || prev->type == TOKEN_QUOTED) && (tmp->type == TOKEN_WORD || tmp->type == TOKEN_QUOTED))
			count++;
		
		prev = tmp ;
		tmp = tmp->next;
	}
	return count ;
}

char **get_args(t_token *token)
{
	t_token *tmp = token;
	t_token *prev ;
	int i = 0;
	int count = count_args(token);
	char **cmd = malloc(sizeof(char*) * (count+2));
	if (!*cmd)
		return NULL;
	if(tmp->type == TOKEN_WORD || tmp->type == TOKEN_QUOTED)
	{
		cmd[i] = ft_strdup(tmp->token);
		i++;
	}
	prev = tmp;
	tmp = tmp->next;
	while (tmp && tmp->type != TOKEN_PIPE) 
	{
		if (( prev->type == TOKEN_PIPE || prev->type == TOKEN_WORD  || prev->type == TOKEN_QUOTED) && (tmp->type == TOKEN_WORD || tmp->type == TOKEN_QUOTED))
		{
			cmd[i] = ft_strdup(tmp->token);
			i++;
		}
		prev = tmp ;
		tmp = tmp->next;
	}
	cmd[i] = NULL;
	return (cmd);
}
