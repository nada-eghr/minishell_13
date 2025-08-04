/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:53:48 by naessgui          #+#    #+#             */
/*   Updated: 2025/08/04 11:42:48 by naessgui         ###   ########.fr       */
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
void remove_dollar_and_quotes_if_needed(t_token *token)
{
    char *new_data;

    if (!token || !token->token)
        return;

    if (token->token[0] == '$' && token->token[1] == '"')
    {
        new_data = substr(token->token, 2, ft_strlen(token->token) - 3);
        free(token->token);
        token->token = ft_strdup(new_data);
        free(new_data);
    }
}
void expand_dollar_in_token(t_token *token, t_env_list *env, int *exit_stat)
{
    int     j;
    char    *s1;
    char    *s2;
    char    *joined;

    if (!token || !token->token || !ft_strchr(token->token, '$'))
        return;

    j = 0;
    while (token->token[j] && token->token[j] != '$')
        j++;

    s1 = substr(token->token, 1, j - 1);  // text before $
    s2 = substr(token->token, j, ft_strlen(token->token) - j - 1);  // the variable name
    joined = ft_strjoin(s1, get_env_or_empty(s2, env, exit_stat));  // substitute env var

    free(token->token);
    token->token = ft_strdup(joined);

    ft_free_exp(s1, s2, joined);
}
void remove_wrapping_quotes(t_token *token)
{
    char *new_data;

    if (!token || !token->token)
        return;

    // Ensure string is at least 2 characters long
    if (ft_strlen(token->token) >= 2)
    {
        new_data = substr(token->token, 1, ft_strlen(token->token) - 2);
        if (!new_data)
            return;

        free(token->token);
        token->token = ft_strdup(new_data);
        free(new_data);
    }
}

void	expand_double_quote(t_token *tmp, t_env_list *env, int *exit_stat)
{
	// int		j;
	// char	*s1;
	// char	*s2;
	// char	*joined;
	// char	*new_data;

	if (tmp->token[0] == '$' && tmp->token[1] == '"')
	{
		remove_dollar_and_quotes_if_needed(tmp);

		// new_data = substr(tmp->token, 2, ft_strlen(tmp->token) - 3);
		// free(tmp->token);
		// tmp->token = ft_strdup(new_data);
		return ;
	}
	if (ft_strchr(tmp->token, '$'))
	{
		expand_dollar_in_token(tmp, env, exit_stat);

		// j = 0;
		// while (tmp->token[j] && tmp->token[j] != '$')
		// 	j++;
		// s1 = substr(tmp->token, 1, j - 1);
		// s2 = substr(tmp->token, j, ft_strlen(tmp->token) - j - 1);
		// joined = ft_strjoin(s1, get_env_or_empty(s2, env, exit_stat));
		// free(tmp->token);
		// tmp->token = ft_strdup(joined);
		// ft_free_exp(s1, s2, joined);
	}
	else
	{
		// new_data = substr(tmp->token, 1, ft_strlen(tmp->token) - 2);
		// free(tmp->token);
		// tmp->token = ft_strdup(new_data);
		// free(new_data);
		remove_wrapping_quotes(tmp);

	}
}

void	expand_word_token(t_token *tmp, t_env_list *env, int *exit_stat)
{
	if (ft_strchr(tmp->token, '$'))
		expand_env_variable(tmp, env, exit_stat);
	else if (ft_strchr(tmp->token, '\'') || ft_strchr(tmp->token, '"'))
		remove_quotes(tmp);
}

void	ft_helper_env(t_token *token, t_env_list *env, int *exit_stat)
{
	t_token	*helper;

	helper = token;
	if (!(token->prev) || (token->prev->type == T_SPACE
			&& token->prev->prev == NULL ))
	{
		// printf("token %s", token->token);
		// printf("1\n");
		expand_env_token(token, env, exit_stat);
		return ;
	}
	while (helper != NULL && helper->type != T_SPACE && helper->type != T_HEREDOC){
			// printf("22\n");
			helper = helper->prev;
		}

if (!(helper) || (helper->type == T_SPACE
			&& helper->prev == NULL ))
	{
		// printf("token %s", token->token);
		// printf("1\n");
		expand_env_token(token, env, exit_stat);
		return ;
	}
if (helper->type != T_HEREDOC &&  helper->prev->type != T_HEREDOC) {
	// printf("lads\n");
    expand_env_token(token, env, exit_stat);	
}
// if (helper == NULL || helper->type == T_SPACE) {
//     expand_env_token(token, env, exit_stat);	
// }
	
}

void	ft_helper(t_token *token, t_env_list *env, int *exit_stat)
{
	// printf("hi\n");
	t_token	*helper;

	helper = token;
	if (!(token->prev) || (token->prev->type == T_SPACE
			&& token->prev->prev == NULL))
	{
		expand_double_quote(token, env, exit_stat);
		return ;
	}
	while (helper != NULL && helper->type != T_SPACE)
		helper = helper->prev;
	// printf("hep = %p\n",helper);
	// return;
	// if ((helper->prev->type != T_HEREDOC && helper->type != T_HEREDOC))
	// printf("helperr %s\n", helper->token);
	if (!(helper) || (helper->type == T_SPACE
			&& helper->prev == NULL ))
	{

		expand_double_quote(token, env, exit_stat);
		return ;
	}
	// if((helper->prev->type != T_HEREDOC && helper->type != T_HEREDOC))
	if (helper->type != T_HEREDOC &&  helper->prev->type != T_HEREDOC)
		expand_double_quote(token, env, exit_stat);
	remove_quotes(token);
}
t_token	*expand_token(t_token *token, t_env_list *env, int *exit_stat)
{
	t_token	*tmp;
	t_token	*prev;

	tmp = token;
	prev = token;
	while (tmp)
	{
		if (tmp->type == T_D_QUOTE)
			ft_helper(tmp, env, exit_stat);
		else if (tmp->type == T_ENV)
			ft_helper_env(tmp, env, exit_stat);
		else if (tmp->type == T_S_QUOTE)
			expand_single_quote(tmp);
		else if (tmp->type == T_WORD)
		{
			if (!ft_strcmp(tmp->token, "$") && tmp->next && ((tmp->next->type == T_D_QUOTE || tmp->next->type == T_S_QUOTE )))
				delete_specific_node(&token, tmp);
			expand_word_token(tmp, env, exit_stat);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (token);
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
