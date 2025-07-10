/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 17:15:41 by naessgui          #+#    #+#             */
/*   Updated: 2025/07/10 10:34:48 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"





char *filter_token(t_token *filter_lst){
    t_token *token;

    char *str = ft_strdup("");
    token = filter_lst;
    
    while(token){
       
        str = ft_strjoin(str, token->token); 
        token = token->next;
    }
    return str;
}


static t_token	*parse_operator_token(const char *data, int *i)
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



static t_token	*parse_word_token(const char *data, int *i)
{
	int		start;
	int		end;
	char	*new;
	t_token	*token;

	start = *i;
	while (data[*i] && !ft_space(data[*i]) && data[*i] != '>' && data[*i] != '<'
		&& data[*i] != '|' )
		(*i)++;
	end = *i;
	new = substr(data, start, end - start);
	token = creattoken(new);
	free(new);
	return (token);
}

t_token	*convert_to_token(char *data)
{
	int		i;
	t_token	*head;
	t_token	*token;

	i = 0;
	head = NULL;
	token = NULL;
	while (data[i])
	{
        if(data[i] && ft_space(data[i]))
        {
            while (ft_space(data[i]))
				i++;
        }
		else if (data[i] == '>' || data[i] == '<' || data[i] == '|')
			token = parse_operator_token(data, &i);
		else 
            token = parse_word_token(data, &i);
		if (token)
			add_back(&head, token);
	}
	return (head);
}