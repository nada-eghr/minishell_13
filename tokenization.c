/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:57:56 by naessgui          #+#    #+#             */
/*   Updated: 2025/06/14 20:23:50 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char loop_quote(char *data, int *i)
{
     char quote = data[*i]; // store the opening quote
            // int start = i;
            (*i)++; 

            while (data[*i] && data[*i] != quote)
                i++;
            // printf("data[%d] = %c\n",i,data[i]);
            
            if (data[*i] == quote) // closing quote found
            {
                if(!ft_space(data[*i + 1]) && data[*i + 1])
                {
                    i++;
                    while(ft_isprint(data[*i]) && data[*i])
                            (*i)++;
                }
            }
}
 
int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	else
		return (0);
}
t_token_type get_token_type(char *token)
{
    int len = ft_strlen(token);
    // printf("token [0] = %c\n",token[0]);
	// printf("token [len - 1] = %c\n",token[len - 1]);
    if (!token)
        return (TOKEN_UNKNOWN);
    if (ft_strcmp(token, "|") == 0)
        return (TOKEN_PIPE);
    if (ft_strcmp(token, "<") == 0)
        return(TOKEN_REDIR_IN);
    if (ft_strcmp(token, ">") == 0)
        return(TOKEN_REDIR_OUT);
    if (ft_strcmp(token, ">>") == 0)
        return(TOKEN_APPEND);
    if (ft_strcmp(token, "<<") == 0)
        return(TOKEN_HERDOC);
   if ((token[0] == '"' && token[len - 1] == '"') ||
        (token[0] == '\'' && token[len - 1] == '\'')) 
        return (TOKEN_QUOTED);
    if (token[0] == '$' && len > 1 && 
    (isalpha(token[1]) || token[1] == '_' || token[1] == '?')) 
        return (TOKEN_ENV_VAR);
    return(TOKEN_WORD);
}


t_token *convert_to_node(char *data)
{
    int i = 0;
    t_token *head = NULL;
    t_token *token = NULL;
    char *new;
    char tmp[256]; 

    while (data[i])
    {
        while (ft_space(data[i]))
            i++;
        if (data[i] == '>' || data[i] == '<' || data[i] == '|')
        {
            int j = 0;

            if ((data[i + 1] == '>' || data[i + 1] == '<') && data[i] != '|')
            {
                tmp[j++] = data[i++];
            }
            tmp[j++] = data[i++];
            tmp[j] = '\0';

            token = creattoken(tmp);
        }
        else if (data[i] == '\"' || data[i] == '\'')
        {
            loop_quote(data,&i);
            
            // char quote = data[i]; // store the opening quote
            int start = i;
            // i++; 

            // while (data[i] && data[i] != quote)
            //     i++;
            // // printf("data[%d] = %c\n",i,data[i]);
            
            // if (data[i] == quote) // closing quote found
            // {
            //     if(!ft_space(data[i + 1]) && data[i + 1]){
            //         i++;
            //         while(ft_isprint(data[i]) && data[i])
            //                 i++;
            //     }
               
                int end = i;
                new = substr(data, start, end - start + 1); // include quotes
                printf("new = %s\n",new);
                token = creattoken(new);
                free(new);
                i++; 
            // }
            // else
            // {
            //     printf("minishell: syntax error: unclosed quote\n");
            //     free_list(head);  // free all previously created tokens
            //     return NULL;      // signal failure
            // }

        }

       // --------------normal word
        else if (data[i] && data[i] != '>' && data[i] != '<' && data[i] != '|' && data[i] != '\"' && data[i]!='\'')
        {
            int j = 0;

            while (data[i] && !ft_space(data[i]) &&
                   data[i] != '>' && data[i] != '<' && data[i] != '|' && data[i] != '\"')
            {
                tmp[j++] = data[i++];
            }
            tmp[j] = '\0';

            token = creattoken(tmp);
        }

        if (token)
        {
            add_back(&head, token);
            token = NULL; 
        }
    }
    
    return head;
}