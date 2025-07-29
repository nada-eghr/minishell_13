/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:53:48 by naessgui          #+#    #+#             */
/*   Updated: 2025/07/29 09:38:34 by naessgui         ###   ########.fr       */
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
	printf("makadkhelch\n");
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

// void	expand_single_quote(t_token *tmp)
// {
// 	char	*new_data;

// 	new_data = substr(tmp->token, 1, ft_strlen(tmp->token) - 2);
// 	free(tmp->token);
// 	tmp->token = ft_strdup(new_data);
// 	free(new_data);
// }
// void	handle_special_dollar_quotes(t_token *tmp)
// {
// 	char *new_data;

// 	// Case: $"USER"
// 	if (tmp && tmp->token[0] == '$' && tmp->token[1] == '"')
// 	{
// 		printf("NADA\n");
// 		new_data = substr(tmp->token, 1, ft_strlen(tmp->token) - 2);
// 		free(tmp->token);
// 		tmp->token = ft_strdup(new_data);
// 		free(new_data);
		
// 	}

// 	// Case: $'USER'
// 	else if (tmp->token[0] == '$' && tmp->token[1] == '\'')
// 	{
// 		new_data = substr(tmp->token, 2, ft_strlen(tmp->token) - 3);
// 		free(tmp->token);
// 		tmp->token = ft_strdup(new_data);
// 		free(new_data);
// 	}
// }



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
		// printf("tokens - %s\n", tmp->token);
		// Existing logic
		// if (tmp->type == T_ENV && (tmp->next->type == T_D_QUOTE ||tmp->next->type == T_S_QUOTE ) )
		// {
		// 	printf("jffkf\n");
		// 	remove_quotes(tmp->next);
		// }
		if (tmp->type == T_ENV && prev->type != T_HEREDOC){
			expand_env_token(tmp, env, exit_stat);
			// printf("2\n");
		}
			
		
		else if (tmp->type == T_D_QUOTE && prev->type != T_HEREDOC){
			// printf("0\n");
			expand_double_quote(tmp, env, exit_stat);
		}
			
		else if (tmp->type == T_S_QUOTE)
		{
			// printf("1 \n");
			expand_single_quote(tmp);
			
		}
		else if (tmp->type == T_WORD ){
			// printf("tmp = %s\n",tmp->token);
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
		// $'string' → remove first 2 chars and last 1 char
		new_data = substr(tmp->token, 2, ft_strlen(tmp->token) - 3);
	}
	else
	{
		// 'string' → remove first and last quote
		new_data = substr(tmp->token, 1, ft_strlen(tmp->token) - 2);
	}
	free(tmp->token);
	tmp->token = ft_strdup(new_data);
	free(new_data);
}

// 	while (tmp)
// 	{
// 		if (tmp->type == T_ENV && prev->type != T_HEREDOC)
// 			expand_env_token(tmp, env, exit_stat);
// 		else if (tmp->type == T_D_QUOTE && prev->type != T_HEREDOC)
// 		{
// 			expand_double_quote(tmp, env, exit_stat);
// 		}
			
// 		else if (tmp->type == T_S_QUOTE){
// 			expand_single_quote(tmp);
// 		}
			
// 		else if (tmp->type == T_WORD)
// 			expand_word_token(tmp, env, exit_stat);
// 		prev = tmp;
// 		tmp = tmp->next;
// 	}
// 	return (token);
// }
// void	expand_double_quote(t_token *tmp, t_env_list *env, int *exit_stat)
// {
// 	char	*new_data;
// 	char	*joined;
// 	char	*s1;
// 	char	*s2;
// 	int		j;

// 	// Handle $"..." → no expansion, just strip $ and quotes
// 	if (tmp->token[0] == '$' && tmp->token[1] == '"')
// 	{
// 		new_data = substr(tmp->token, 2, ft_strlen(tmp->token) - 3);
// 		free(tmp->token);
// 		tmp->token = ft_strdup(new_data);
// 		free(new_data);
// 		return;
// 	}

// 	// Regular double quote with potential variable expansion
// 	if (ft_strchr(tmp->token, '$'))
// 	{
// 		j = 0;
// 		while (tmp->token[j] && tmp->token[j] != '$')
// 			j++;
// 		s1 = substr(tmp->token, 1, j - 1);
// 		s2 = substr(tmp->token, j, ft_strlen(tmp->token) - j - 1);
// 		joined = ft_strjoin(s1, get_env_or_empty(s2, env, exit_stat));
// 		free(tmp->token);
// 		tmp->token = ft_strdup(joined);
// 		ft_free_exp(s1, s2, joined);
// 	}
// 	else
// 	{
// 		new_data = substr(tmp->token, 1, ft_strlen(tmp->token) - 2);
// 		free(tmp->token);
// 		tmp->token = ft_strdup(new_data);
// 		free(new_data);
// 	}
// }


// void	expand_single_quote(t_token *tmp)
// {
// 	printf("Original token: [%s]\n", tmp->token);

// 	char *new_data;
// 	if (tmp->token[0] == '$' && tmp->token[1] == '\'')
// 	{
// 		// $'string' => skip $' and remove last quote
// 		new_data = substr(tmp->token, 2, ft_strlen(tmp->token) - 3);
// 	}
// 	else
// 	{
// 		// 'string' => remove first and last quote
// 		new_data = substr(tmp->token, 1, ft_strlen(tmp->token) - 2);
// 	}

// 	printf("After expansion: [%s]\n", new_data);

// 	free(tmp->token);
// 	tmp->token = ft_strdup(new_data);
// 	free(new_data);
// }