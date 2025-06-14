/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 13:08:55 by naessgui          #+#    #+#             */
/*   Updated: 2025/06/14 16:53:57 by naessgui         ###   ########.fr       */
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
char	*ft_strncpy(char *dst, const char *src, size_t n)
{
	size_t i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dst[i] = '\0';
		i++;
	}
	return (dst);
}
char *substr(const char *src, int start, int len)
{
    char *res = malloc(len + 1);
    if (!res) 
        return NULL;
    ft_strncpy(res, src + start, len);
    res[len] = '\0';
    return res;
}

int			ft_space(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}
char *ft_strdup(char *s)
{
	int i = 0;
	char *cp = malloc(sizeof(char) * (strlen(s) + 1));
	if (!cp)
		return NULL;
	while(s[i])
	{
		cp[i] = s[i];
		i++;
	}
	cp[i] = '\0';
	return cp;
}