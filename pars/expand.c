/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slamhaou <slamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:53:48 by naessgui          #+#    #+#             */
/*   Updated: 2025/08/01 18:42:46 by slamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand_env_token(t_token *tmp, t_env_list *env, int *exit_stat)
{
	char	*new_data;

	new_data = get_env_or_empty(tmp->token, env, exit_stat);
	free(tmp->token);
	tmp->token = new_data;
}

void	expand_double_quote(t_token *tmp, t_env_list *env, int *exit_stat)
{
	int		j;
	char	*s1;
	char	*s2;
	char	*joined;
	char	*new_data;
	if (tmp->token[0] == '$' && tmp->token[1] == '"')
{
	new_data = substr(tmp->token, 2, ft_strlen(tmp->token) - 3);
	free(tmp->token);
	tmp->token = ft_strdup(new_data);
	return;
}

	if (ft_strchr(tmp->token, '$'))
	{
		j = 0;
		while (tmp->token[j] && tmp->token[j] != '$')
			j++;
		s1 = substr(tmp->token, 1, j - 1);
		s2 = substr(tmp->token, j, ft_strlen(tmp->token) - j - 1);
		joined = ft_strjoin(s1, get_env_or_empty(s2, env, exit_stat));
		free(tmp->token);
		tmp->token = ft_strdup(joined);
		ft_free_exp(s1, s2, joined);
	}
	else
	{
		new_data = substr(tmp->token, 1, ft_strlen(tmp->token) - 2);
		free(tmp->token);
		tmp->token = ft_strdup(new_data);
		free(new_data);
	}
}

void	expand_word_token(t_token *tmp, t_env_list *env, int *exit_stat)
{
	if (ft_strchr(tmp->token, '$'))
		expand_env_variable(tmp, env, exit_stat);
	else if (ft_strchr(tmp->token, '\'') || ft_strchr(tmp->token, '"'))
		remove_quotes(tmp);
}

t_token	*expand_token(t_token *token, t_env_list *env, int *exit_stat)
{
	t_token	*tmp;
	t_token	*prev;

	tmp = token;
	prev = token;
	while (tmp)
	{
		if (tmp->type == T_ENV && prev->type != T_HEREDOC){
			expand_env_token(tmp, env, exit_stat);
		}
			
		
		else if (tmp->type == T_D_QUOTE && prev->type != T_HEREDOC){
			expand_double_quote(tmp, env, exit_stat);
		}
			
		else if (tmp->type == T_S_QUOTE)
		{
			expand_single_quote(tmp);
			
		}
		else if (tmp->type == T_WORD ){
			if(!strcmp(tmp->token, "$"))
				delete_specific_node(&token, tmp);
			expand_word_token(tmp, env, exit_stat);
		}
			

		prev = tmp;
		tmp = tmp->next;
	}
	return token;
}
void	expand_single_quote(t_token *tmp)
{
	char	*new_data;

	if (tmp->token[0] == '$' && tmp->token[1] == '\'')
	{
		new_data = substr(tmp->token, 2, ft_strlen(tmp->token) - 3);
	}
	else
	{
		new_data = substr(tmp->token, 1, ft_strlen(tmp->token) - 2);
	}
	free(tmp->token);
	tmp->token = ft_strdup(new_data);
	free(new_data);
}

