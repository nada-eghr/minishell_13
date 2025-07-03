/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:53:48 by naessgui          #+#    #+#             */
/*   Updated: 2025/07/02 20:15:47 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include"minishell.h"

char *get_value(char *str, t_env_list *env)
{
    t_env_list *tmp;
    char *s = ft_strdup(""); 
    char *content;
    int nb = 127;
    char *status;
    int found = 0;

    while (*str)
    {
        if (*str == '$' && (*(str + 1) == '$' || *(str + 1) == '?'))
        {
            status = ft_itoa(nb); 
            str += 2; 
            char *temp = ft_strjoin(s, status);
            free(s); 
            free(status); 
            s = temp; 
        }
        else if (*str == '$' && (isalpha(*(str + 1)) || *(str + 1)))
        {
            str++;
            if (*str == '\'' || *str == '"')
            {
                str++;
                while ( *str && *str != '\'' && *str != '"')
                {
                    char *temp = ft_strjoin(s, (char[]){*str, '\0'});
                    free(s);
                    s = temp;
                    str++;
                }
            }
            tmp = env;
            if (env == NULL)
                return ft_strdup("");
            while (tmp)
            {
                if (ft_strncmp(str, tmp->content.key, ft_strlen(tmp->content.key)) == 0)
                {
                    if (*(str + ft_strlen(tmp->content.key)) == '$' || *(str + ft_strlen(tmp->content.key)) == '\0' || *(str + ft_strlen(tmp->content.key)) == ' ')
                    {
                        found = 1;
                        content = tmp->content.value;
                        char *temp = ft_strjoin(s, content);
                        free(s);
                        s = temp;
                        str += ft_strlen(tmp->content.key);
                        break;
                    }
                    else
                    {
                        while (*str && *str != '$' && *str != ' ')
                            str++;
                        char *temp = ft_strjoin(s, ft_strdup(""));
                            free(s);
                            s = temp;
                        break;
                    }
                }
                tmp = tmp->next;
            }
            if (found == 0)
            {
                while (*str && *str != '$' && *str != ' ')
                        str++;
                char *temp = ft_strjoin(s, ft_strdup(""));
                free(s);
                s = temp;
            }
            
        }
        else if (*str == '$' && (*(str + 1) == '\0' || *(str + 1) == ' '))
        {
            
            char *temp = ft_strjoin(s,"$");
            free(s); 
            s = temp; 
            str++;
        }
        else if ( *str == '?'&& (*(str + 1) == '\0' || *(str + 1) == ' '))
        {
            
            char *temp = ft_strjoin(s,"?");
            free(s); 
            s = temp; 
            str++;
        }
        else
        {

            char *temp = ft_strjoin(s, (char[]){*str, '\0'});
            free(s); 
            s = temp; 
            str++;
        }
    }
    return s;
}
char *get_env_or_empty(char *key, t_env_list *env)
{
    char *new_data = get_value(key, env);
    char *value ;
    if (new_data)
        value = ft_strdup(new_data);
    else
        value = ft_strdup("");
    free(new_data);
    return value;
}
               

void expand_env_token(t_token *tmp, t_env_list *env)
{
    char *new_data = get_env_or_empty(tmp->token, env);
    free(tmp->token);
    tmp->token = new_data;
}

void expand_double_quote(t_token *tmp, t_env_list *env)
{
    if (ft_strchr(tmp->token, '$'))
    {
        int j = 0;
        while (tmp->token[j] && tmp->token[j] != '$')
            j++;
        char *s1 = substr(tmp->token, 1, j - 1);
        char *s2 = substr(tmp->token, j, ft_strlen(tmp->token) - j - 1);
        char *val = get_env_or_empty(s2, env);
        char *joined = ft_strjoin(s1, val);

        free(tmp->token);
        tmp->token = ft_strdup(joined);

        free(s1);
        free(s2);
        free(val);
        free(joined);
    }
    else
    {
        char *new_data = substr(tmp->token, 1, ft_strlen(tmp->token) - 2);
        free(tmp->token);
        tmp->token = ft_strdup(new_data);
        free(new_data);
    }
}

void expand_single_quote(t_token *tmp)
{
    char *new_data = substr(tmp->token, 1, ft_strlen(tmp->token) - 2);
    free(tmp->token);
    tmp->token = ft_strdup(new_data);
    free(new_data);
}

void expand_word_token(t_token *tmp, t_env_list *env)
{
    if (ft_strchr(tmp->token, '$'))
    {
        int j = 0;
        while (tmp->token[j] && tmp->token[j] != '$')
            j++;
        char *s1 = substr(tmp->token, 0, j);
        char *s2 = substr(tmp->token, j, ft_strlen(tmp->token) - j);
        char *val = get_env_or_empty(s2, env);
        char *joined = ft_strjoin(s1, val);

        free(tmp->token);
        tmp->token = ft_strdup(joined);

        free(s1);
        free(s2);
        free(val);
        free(joined);
    }
    else if (ft_strchr(tmp->token, '\'') || ft_strchr(tmp->token, '"'))
    {
        char *str = malloc(ft_strlen(tmp->token) + 1);
        int i = 0, j = 0;
        while (tmp->token[i])
        {
            if (tmp->token[i] != '\'' && tmp->token[i] != '"')
                str[j++] = tmp->token[i];
            i++;
        }
        str[j] = '\0';

        free(tmp->token);
        tmp->token = ft_strdup(str);
        free(str);
    }
}

t_token *expand_token(t_token *token, t_env_list *env)
{
    t_token *tmp = token;
    t_token *prev = token;

    while (tmp)
    {
        if (tmp->type == T_ENV && prev->type != T_HEREDOC)
            expand_env_token(tmp, env);

        else if (tmp->type == T_D_QUOTE && prev->type != T_HEREDOC)
            expand_double_quote(tmp, env);

        else if (tmp->type == T_S_QUOTE)
            expand_single_quote(tmp);

        else if (tmp->type == T_WORD)
            expand_word_token(tmp, env);

        prev = tmp;
        tmp = tmp->next;
    }

    return token;
}
