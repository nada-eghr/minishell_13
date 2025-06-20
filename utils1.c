/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 10:43:37 by naessgui          #+#    #+#             */
/*   Updated: 2025/06/20 16:50:16 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	else
		return (0);
}
int	ft_space(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

char	*ft_strjoin(char *s1, char *s2)
{
	int	i;
	int j;
	char	*str;

	i = 0;
	j= 0;
	if (!s1 && !s2)
		return (NULL);
	if (s1 && !s2)
		return (ft_strdup(s1));
	if (!s1 && s2)
		return (ft_strdup(s2));
	str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	while ( s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while(s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return str;
}
char	*ft_strchr(char *s, int c)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(s);
	while (i <= len)
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	return (NULL);
}