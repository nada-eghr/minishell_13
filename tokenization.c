/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:57:56 by naessgui          #+#    #+#             */
/*   Updated: 2025/06/15 17:13:30 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_type	get_token_type(char *token)
{
	int	len;

	len = ft_strlen(token);
	if (!token)
		return (TOKEN_UNKNOWN);
	if (ft_strcmp(token, "|") == 0)
		return (TOKEN_PIPE);
	if (ft_strcmp(token, "<") == 0)
		return (TOKEN_REDIR_IN);
	if (ft_strcmp(token, ">") == 0)
		return (TOKEN_REDIR_OUT);
	if (ft_strcmp(token, ">>") == 0)
		return (TOKEN_APPEND);
	if (ft_strcmp(token, "<<") == 0)
		return (TOKEN_HERDOC);
	if ((token[0] == '"' && token[len - 1] == '"') || (token[0] == '\''
			&& token[len - 1] == '\''))
		return (TOKEN_QUOTED);
	if (token[0] == '$' && len > 1 && (isalpha(token[1]) || token[1] == '_'
			|| token[1] == '?'))
		return (TOKEN_ENV_VAR);
	return (TOKEN_WORD);
}

t_token	*parse_operator_token(const char *data, int *i)
{
	int		j;
	char	tmp[3];

	j = 0;
	if ((data[*i + 1] == '>' || data[*i + 1] == '<') && data[*i] != '|')
		tmp[j++] = data[(*i)++];
	tmp[j++] = data[(*i)++];
	tmp[j] = '\0';
	return (creattoken(tmp));
}

t_token	*parse_quoted_token(const char *data, int *i, t_token **head)
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
	if (!data[*i])
	{
		printf("minishell: syntax error: unclosed quote\n");
		return (free_list(*head), NULL);
	}
	(*i)++;
	if (!ft_space(data[*i]) && data[*i])
	{
		while (ft_isprint(data[*i]) && data[*i] && !ft_space(data[*i]))
			(*i)++;
	}
	end = *i;
	new = substr(data, start, end - start);
	token = creattoken(new);
	return (free(new), token);
}

t_token	*parse_word_token(const char *data, int *i)
{
	char	tmp[256];
	int		j;

	j = 0;
	while (data[*i] && !ft_space(data[*i]) && data[*i] != '>' && data[*i] != '<'
		&& data[*i] != '|' && data[*i] != '\"' && data[*i] != '\'')
	{
		tmp[j++] = data[(*i)++];
	}
	tmp[j] = '\0';
	return (creattoken(tmp));
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
