/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dq_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 13:40:12 by naessgui          #+#    #+#             */
/*   Updated: 2025/08/10 17:26:53 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_helper_env(t_token *token, t_env_list *env, int *exit_stat)
{
	t_token	*helper;

	helper = token;
	if (!(token->prev) || (token->prev->type == T_SPACE
			&& token->prev->prev == NULL))
	{
		expand_env_token(token, env, exit_stat);
		return ;
	}
	while (helper != NULL && helper->type != T_SPACE
		&& helper->type != T_HEREDOC)
		helper = helper->prev;
	if (!(helper) || (helper->type == T_SPACE && helper->prev == NULL))
	{
		expand_env_token(token, env, exit_stat);
		return ;
	}
	if (helper->type != T_HEREDOC && helper->prev->type != T_HEREDOC)
		expand_env_token(token, env, exit_stat);
}

void	ft_helper(t_token *token, t_env_list *env, int *exit_stat)
{
	t_token	*helper;

	helper = token;
	if (!(token->prev) || (token->prev->type == T_SPACE
			&& token->prev->prev == NULL))
	{
		expand_double_quote(token, env, exit_stat);
		return ;
	}
	while (helper != NULL && helper->type != T_SPACE
		&& helper->type != T_HEREDOC)
		helper = helper->prev;
	if (!(helper) || (helper->type == T_SPACE && helper->prev == NULL))
	{
		expand_double_quote(token, env, exit_stat);
		return ;
	}
	if (helper->type != T_HEREDOC && helper->prev->type != T_HEREDOC)
		expand_double_quote(token, env, exit_stat);
	remove_quotes(token);
}

void	remove_dollar_and_quotes_if_needed(t_token *token)
{
	char	*new_data;

	if (!token || !token->token)
		return ;
	if (token->token[0] == '$' && token->token[1] == '"')
	{
		new_data = substr(token->token, 2, ft_strlen(token->token) - 3);
		free(token->token);
		token->token = ft_strdup(new_data);
		free(new_data);
	}
}

void	expand_dollar_in_token(t_token *token, t_env_list *env, int *exit_stat)
{
	int		j;
	char	*s1;
	char	*s2;
	char	*value;
	char	*joined;

	if (!token || !token->token || !ft_strchr(token->token, '$'))
		return ;
	j = 0;
	while (token->token[j] && token->token[j] != '$')
		j++;
	s1 = substr(token->token, 1, j - 1);
	s2 = substr(token->token, j, ft_strlen(token->token) - j - 1);
	value = get_env_or_empty(s2, env, exit_stat);
	joined = ft_strjoin(s1, value, N_FREE);
	free(value);
	free(token->token);
	token->token = ft_strdup(joined);
	ft_free_exp(s1, s2, joined);
}

void	expand_double_quote(t_token *tmp, t_env_list *env, int *exit_stat)
{
	if (tmp->token[0] == '$' && tmp->token[1] == '"')
	{
		remove_dollar_and_quotes_if_needed(tmp);
		return ;
	}
	if (ft_strchr(tmp->token, '$'))
		expand_dollar_in_token(tmp, env, exit_stat);
	else
		remove_wrapping_quotes(tmp);
}
