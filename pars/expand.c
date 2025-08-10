// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   expand.c                                           :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/06/18 18:53:48 by naessgui          #+#    #+#             */
// /*   Updated: 2025/08/10 12:12:02 by naessgui         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../minishell.h"

// void	expand_env_token(t_token *tmp, t_env_list *env, int *exit_stat)
// {
// 	char	*new_data;

// 	new_data = get_env_or_empty(tmp->token, env, exit_stat);
// 	free(tmp->token);
// 	tmp->token = new_data;
// }

// void	expand_word_token(t_token *tmp, t_env_list *env, int *exit_stat)
// {
// 	if (ft_strchr(tmp->token, '$'))
// 		expand_env_variable(tmp, env, exit_stat);
// 	else if (ft_strchr(tmp->token, '\'') || ft_strchr(tmp->token, '"'))
// 		remove_quotes(tmp);
// }

// void	expand_single_quote(t_token *tmp)
// {
// 	char	*new_data;

// 	if (tmp->token[0] == '$' && tmp->token[1] == '\'')
// 		new_data = substr(tmp->token, 2, ft_strlen(tmp->token) - 3);
// 	else
// 		new_data = substr(tmp->token, 1, ft_strlen(tmp->token) - 2);
// 	free(tmp->token);
// 	tmp->token = ft_strdup(new_data);
// 	free(new_data);
// }

// t_token	*process_token(t_token *tmp, t_token **head, t_env_list *env,
// 		int *exit_stat)
// {
// 	t_token	*next;

// 	if (tmp->type == T_D_QUOTE)
// 		ft_helper(tmp, env, exit_stat);
// 	else if (tmp->type == T_ENV)
// 		ft_helper_env(tmp, env, exit_stat);
// 	else if (tmp->type == T_S_QUOTE)
// 		expand_single_quote(tmp);
// 	else if (tmp->type == T_WORD)
// 	{
// 		if (str_cmp(tmp->token, "$") && tmp->next
// 			&& (tmp->next->type == T_D_QUOTE || tmp->next->type == T_S_QUOTE))
// 		{
// 			next = tmp->next;
// 			delete_specific_node(head, tmp);
// 			tmp = next;
// 		}
// 		expand_word_token(tmp, env, exit_stat);
// 	}
// 	return (tmp->next);
// }

// t_token	*expand_token(t_token *token, t_env_list *env, int *exit_stat)
// {
// 	t_token	*tmp;

// 	tmp = token;
// 	while (tmp)
// 		tmp = process_token(tmp, &token, env, exit_stat);
// 	return (token);
// }
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:53:48 by naessgui          #+#    #+#             */
/*   Updated: 2025/08/05 16:56:19 by naessgui         ###   ########.fr       */
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

void	expand_word_token(t_token *tmp, t_env_list *env, int *exit_stat)
{
	if (ft_strchr(tmp->token, '$'))
		expand_env_variable(tmp, env, exit_stat);
	else if (ft_strchr(tmp->token, '\'') || ft_strchr(tmp->token, '"'))
		remove_quotes(tmp);
}

void	expand_single_quote(t_token *tmp)
{
	char	*new_data;

	if (tmp->token[0] == '$' && tmp->token[1] == '\'')
		new_data = substr(tmp->token, 2, ft_strlen(tmp->token) - 3);
	else
		new_data = substr(tmp->token, 1, ft_strlen(tmp->token) - 2);
	free(tmp->token);
	tmp->token = ft_strdup(new_data);
	free(new_data);
}

t_token    *process_token(t_token *tmp, t_token **head, t_env_list *env,
        int *exit_stat)
{
    t_token    *next;

    if (tmp->type == T_D_QUOTE)
        ft_helper(tmp, env, exit_stat);
    else if (tmp->type == T_ENV)
        ft_helper_env(tmp, env, exit_stat);
    else if (tmp->type == T_S_QUOTE)
        expand_single_quote(tmp);
    else if (tmp->type == T_WORD)
    {
        if (str_cmp(tmp->token, "$") && tmp->next
            && (tmp->next->type == T_D_QUOTE || tmp->next->type == T_S_QUOTE))
        {
            next = tmp->next;
            delete_specific_node(head, tmp);
            tmp = next;
        }
        expand_word_token(tmp, env, exit_stat);
    }
    return (tmp->next);
}

t_token    *expand_token(t_token *token, t_env_list *env, int *exit_stat)
{
    t_token    *tmp;

    tmp = token;
    while (tmp)
        tmp = process_token(tmp, &token, env, exit_stat);
    return (token);
}
