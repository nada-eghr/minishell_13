/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 21:19:23 by naessgui          #+#    #+#             */
/*   Updated: 2025/07/03 09:44:14 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_quotes(char *str)
{
    int s_quote = 0;
    int d_quote = 0;
    while(*str)
    {
        if (*str == '\'')
        {
            s_quote = 1;
            str++;
            while (*str && *str != '\''){
                str++;
            }
            if (*str == '\'')
                s_quote = 0;    
        }
        else if (*str == '"')
        {
            d_quote = 1;
            str++;
            while (*str && *str != '"')
                str++;
            if (*str == '"')
                d_quote = 0;
        }
        str++;
    }
    if (s_quote || d_quote)
    {
        printf("minishell: unclosed quotes\n");
        return 1; 
    }
    return 0; 
}
