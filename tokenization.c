/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:57:56 by naessgui          #+#    #+#             */
/*   Updated: 2025/06/18 17:30:46 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	loop_quote(char *data, int *i)
// {
// 	char quote = data[*i]; // store the opening quote
// 	// int start = i;
// 	(*i)++;
// 	while (data[*i] && data[*i] != quote)
// 		i++;
// 	// printf("data[%d] = %c\n",i,data[i]);
// 	if (data[*i] == quote) // closing quote found
// 	{
// 		if (!ft_space(data[*i + 1]) && data[*i + 1])
// 		{
// 			i++;
// 			while (ft_isprint(data[*i]) && data[*i])
// 				(*i)++;
// 		}
// 	}
// }

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
	if (token[0] == '"' && token[len - 1] == '"')
		return (TOKEN_D_QUOTE);
	if (token[0] == '\'' && token[len - 1] == '\'')
		return (TOKEN_S_QUOTE);
	if (token[0] == '$' && len > 1 && (isalpha(token[1]) || token[1] == '_'
			|| token[1] == '?'))
		return (TOKEN_ENV_VAR);
	return (TOKEN_WORD);
}

t_token *parse_operator_token(const char *data, int *i)
{
	char tmp[3]; // enough for >> or <<
	int j = 0;

	if (((data[*i] == '>' &&  data[*i + 1] == '>') || (data[*i] == '<' && data[*i + 1] == '<')) && data[*i] != '|')
		tmp[j++] = data[(*i)++];
	tmp[j++] = data[(*i)++];
	tmp[j] = '\0';

	return creattoken(tmp);
}

t_token *parse_quoted_token(const char *data, int *i, t_token **head)
{
	char quote = data[*i];
	int start = (*i)++;

	while (data[*i] && data[*i] != quote)
		(*i)++;

	if (!data[*i]) {
		printf("minishell: syntax error: unclosed quote\n");
		free_list(*head);
		return NULL;
	}
	(*i)++; // move past closing quote
	if (!ft_space(data[*i]) && data[*i]) {
		while (ft_isprint(data[*i]) && data[*i] && !ft_space(data[*i]))
			(*i)++;
	}

	int end = *i;
	char *new = substr(data, start, end - start);
	t_token *token = creattoken(new);
	free(new);
	return token;
}

t_token *parse_word_token(const char *data, int *i)
{
    int start ;
    start = *i;
    while (data[*i] && !ft_space(data[*i]) && data[*i] != '>'
        && data[*i] != '<' && data[*i] != '|' && data[*i] != '\"'
        && data[*i] != '\'')
    {
        if((data[*i + 1] == '\"' && data[*i ])  || (data[*i + 1] == '\'' && data[*i]))
        {
            (*i)++;
            char quote = data[*i];
            (*i)++;
            while (data[*i] != quote)
                (*i)++;
            // printf("data[%d] = %c\n",*i, data[*i]);
        }
        (*i)++;
    }
    int end = *i;
    char *new = substr(data, start, end - start);
    
    t_token *token = creattoken(new);
    // printf("token1 = %s\n", token->token);
    free(new);
    return token;
}

t_token *convert_to_node(char *data)
{
	int i;
	t_token *head ;
	t_token *token ;
	
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
				return NULL;
		}
		else
			token = parse_word_token(data, &i);
		if (token)
			add_back(&head, token);
	}
	return head;
}



// t_token	*convert_to_node(char *data)
// {
// 	int i = 0;
// 	t_token *head = NULL;
// 	t_token *token = NULL;
// 	char *new;
// 	char tmp[256];

// 	while (data[i])
// 	{
// 		while (ft_space(data[i]))
// 			i++;
// 		if (data[i] == '>' || data[i] == '<' || data[i] == '|')
// 		{
// 			int j = 0;

// 			if ((data[i + 1] == '>' || data[i + 1] == '<') && data[i] != '|')
// 			{
// 				tmp[j++] = data[i++];
// 			}
// 			tmp[j++] = data[i++];
// 			tmp[j] = '\0';

// 			token = creattoken(tmp);
// 		}
// 		else if (data[i] == '\"' || data[i] == '\'')
// 		{
// 			// loop_quote(data, &i);

// 			char quote = data[i]; // store the opening quote
// 			int start = i;
// 			i++;

// 			while (data[i] && data[i] != quote)
// 			    i++;
// 			// printf("data[%d] = %c\n",i,data[i]);

// 			if (data[i] == quote) // closing quote found
// 			{
// 			    if(!ft_space(data[i + 1]) && data[i + 1]){
// 			        i++;
// 					printf("data[%d] = %c\n",i,data[i]);
// 			        while(ft_isprint(data[i]) && data[i] && !ft_space(data[i]))
// 			                i++;
// 			    }

// 			int end = i;
// 			new = substr(data, start, end - start + 1); // include quotes
// 			printf("new = %s\n", new);
// 			token = creattoken(new);
// 			free(new);
// 			i++;
// 			}
// 			else
// 			{
// 			    printf("minishell: syntax error: unclosed quote\n");
// 			    free_list(head);  // free all previously created tokens
// 			    return (NULL);      // signal failure
// 			}
// 		}

// 		// --------------normal word
// 		else if (data[i] && data[i] != '>' && data[i] != '<' && data[i] != '|'
// 			&& data[i] != '\"' && data[i] != '\'')
// 		{
// 			int j = 0;

// 			while (data[i] && !ft_space(data[i]) && data[i] != '>'
// 				&& data[i] != '<' && data[i] != '|' && data[i] != '\"')
// 			{
// 				tmp[j++] = data[i++];
// 			}
// 			tmp[j] = '\0';

// 			token = creattoken(tmp);
// 		}

// 		if (token)
// 		{
// 			add_back(&head, token);
// 			token = NULL;
// 		}
// 	}

// 	return (head);
// }