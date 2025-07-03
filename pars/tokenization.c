/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:57:56 by naessgui          #+#    #+#             */
/*   Updated: 2025/07/03 09:27:54 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_type	get_token_type(char *token)
{
	int	len;

	len = ft_strlen(token);
	if (!token)
		return (T_UNKNOWN);
	if (ft_strcmp(token, "|") == 0)
		return (T_PIPE);
	if (ft_strcmp(token, "<") == 0)
		return (T_RED_IN);
	if (ft_strcmp(token, ">") == 0)
		return (T_RED_OUT);
	if (ft_strcmp(token, ">>") == 0)
		return (T_APPEND);
	if (ft_strcmp(token, "<<") == 0)
		return (T_HEREDOC);
	if (token[0] == '"' && token[len - 1] == '"')
		return (T_D_QUOTE);
	if (token[0] == '\'' && token[len - 1] == '\'')
		return (T_S_QUOTE);
	if (token[0] == '$' && len > 1 && (isalpha(token[1]) || token[1] == '_'
			|| token[1] == '?'))
		return (T_ENV);
	return (T_WORD);
}

t_token	*parse_operator_token(const char *data, int *i)
{
	int	j;

	char tmp[3]; // enough for >> or <<
	j = 0;
	if (((data[*i] == '>' && data[*i + 1] == '>') || (data[*i] == '<' && data[*i
				+ 1] == '<')) && data[*i] != '|')
		tmp[j++] = data[(*i)++];
	tmp[j++] = data[(*i)++];
	tmp[j] = '\0';
	return (creattoken(tmp));
}

t_token	*parse_quoted_token(const char *data, int *i, __unused t_token **head)
{
	char	quote;
	int		start;
	int		end;
	char	*new;
	t_token	*token;

	quote = data[*i];
	start = (*i)++;
	while (data[*i] && data[*i] != quote)
		(*i)++;
	// if (!data[*i])
	// {
	// 	printf("minishell: syntax error: unclosed quote\n");
	// 	return (free_list(*head) , NULL);
	// }
	(*i)++; // move past closing quote
	if (!ft_space(data[*i]) && data[*i])
	{
		while (ft_isprint(data[*i]) && data[*i] && !ft_space(data[*i]))
			(*i)++;
	}
	end = *i;
	new = substr(data, start, end - start);
	token = creattoken(new);
	return (free(new),token);
}

t_token	*parse_word_token(const char *data, int *i)
{
	int		start;
	char	quote;
	int		end;
	char	*new;
	t_token	*token;

	start = *i;
	while (data[*i] && !ft_space(data[*i]) && data[*i] != '>' && data[*i] != '<'
		&& data[*i] != '|' && data[*i] != '\"' && data[*i] != '\'')
	{
		if ((data[*i + 1] == '\"' && data[*i]) || (data[*i + 1] == '\''
				&& data[*i]))
		{
			(*i)++;
			quote = data[*i];
			(*i)++;
			while (data[*i] != quote)
				(*i)++;
		}
		(*i)++;
	}
	end = *i;
	new = substr(data, start, end - start);
	token = creattoken(new);
	free(new);
	return (token);
}

t_token	*convert_to_node(char *data)
{
	int		i;
	t_token	*head;
	t_token	*token;

	i = 0;
	head = NULL;
	token = NULL;
	while (data[i])
	{
		while (ft_space(data[i]))
			i++;
		if (data[i] == '>' || data[i] == '<' || data[i] == '|')
			token = parse_operator_token(data, &i);
		else if (data[i] == '\'' || data[i] == '"')
		{
			token = parse_quoted_token(data, &i, &head);
			if (!token)
				return (NULL);
		}
		else
			token = parse_word_token(data, &i);
		if (token)
			add_back(&head, token);
	}
	return (head);
}
