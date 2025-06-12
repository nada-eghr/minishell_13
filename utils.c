/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 13:08:55 by naessgui          #+#    #+#             */
/*   Updated: 2025/05/24 13:10:30 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_strcmp(char *s1, char *s2)                                                                                                                                                                       
{
	int i=0;
    while (s1[i] || s2[i])
    {
        if (s1[i] != s2[i])
            return (s1[i] - s2[i]);
		i++;
    }
    return 0;
}

int ft_strlen(char *str)
{
    int i ;
    i = 0;
    while( str[i] )
        i++;
    return i;
}

char *substr(const char *src, int start, int len)
{
    char *res = malloc(len + 1);
    if (!res) return NULL;
    strncpy(res, src + start, len);
    res[len] = '\0';
    return res;
}

int			ft_space(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}