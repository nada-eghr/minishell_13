/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 15:57:56 by naessgui          #+#    #+#             */
/*   Updated: 2025/06/03 21:50:43 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

t_token_type get_token_type(char *token)
{
    int len = ft_strlen(token);
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
            char quote = data[i]; // store the opening quote
            int start = i;
            i++; 

            while (data[i] && data[i] != quote)
                i++;

            if (data[i] == quote) // closing quote found
            {
                int end = i;
                new = substr(data, start, end - start + 1); // include quotes
                token = creattoken(new);
                free(new);
                i++; 
            }
            else
            {
                printf("minishell: syntax error: unclosed quote\n");
                free_list(head);  // free all previously created tokens
                return NULL;      // signal failure
            }

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

// // void ll()
// // {
// //     system("leaks -q a.out");
// // }

// int main() {
//      //atexit(ll);
//    // while(1)
//     {char *input = readline("minishell$");
//     t_token *tokens = convert_to_node(input);
//     int count = count_args(tokens);
//     int nb = count_outfiles(tokens);
//     int n = count_infiles(tokens);
//     printf("the number of infiles is %d \n", n);
//     printf("the number of outfiles is %d \n", nb);
//      printf("the number of args is %d\n", count);
//     char **cmd = get_args(tokens);
//     int i = 0;
//     while (count  >= 0)
//     {
//          printf("cmd[%d] = %s\n",i,cmd[i]);
//         //printf("%s\n", cmd[i]);
//         count--;
//         i++;
//     }
//     char **infiles = get_infiles(tokens);
//     int j = 0;
//     while (n >= 0)
//     {
//         printf("infiles[%d] = %s\n",j,infiles[j]);
//         n--;
//         j++;
//     }
//     char **outfiles = get_outfiles(tokens);
//     int k = 0;
//     while (nb >= 0)
//     {
//         printf("outfiles[%d] = %s\n",k,outfiles[k]);
//         nb--;
//         k++;
//     }

    
//     int cnt = count_append_files(tokens);
//     char **append_files = get_append_files(tokens);
//     int a = 0;
//     while (cnt >= 0)
//     {
//         printf("append_files[%d] = %s\n",a,append_files[a]);
//         cnt--;
//         a++;
//     }
//     int tmp = count_herdoc_files(tokens);
//     char **herdoc_files = get_herdoc_files(tokens);
//     int h= 0;
//     while (tmp >= 0)
//     {
//         printf("herdocfiles[%d] = %s\n",h,herdoc_files[h]);
//         tmp--;
//         h++;
//     }
    

    
//     if(!tokens)
//     {
//         free(tokens);
//         return 0;
//     }
//     if (check_error(&tokens) == 1)
//     {
//        // printf("minishell : syntax error"); /*free*/
//         free_list(tokens);
//         return 0;
//     }
//     // t_cmd *cmd = convert_to_cmd(&tokens)
//     //------------
//     // t_token *current = tokens;

//     // while (current) {
//     //     printf("{token -> %s } ", current->token);
//     //     printf("{type -> %d } ", current->type);
//     //     current = current->next;
//     // }
//     printf("\n");

//    // printLinkedList(tokens);
    
    
    
//     // Free memory if needed
//     free_list(tokens);
// }
//     return 0;
// }



//         // else if (data[i] == '\"' || data[i] == '\'')
//         // {
//         //     int start = i;
//         //     i++; 

//         //     while (data[i] && data[i] != '\"' && data[i] != '\'')
//         //         i++;

//         //     if (data[i] == '\"' || data[i] == '\'')
//         //     {
//         //         int end = i;
//         //         new = substr(data, start, end - start + 1);
//         //         token = creattoken(new);
//         //         free(new);
//         //         i++; 
//         //     }
           