/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slamhaou <slamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:24:56 by slamhaou          #+#    #+#             */
/*   Updated: 2025/05/28 19:30:00 by slamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heder_shell.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
char	*str_dup(char *s)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc(ft_strlen(s) + 1);
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
char	*str_join(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 && s2)
		return (str_dup(s2));
	if (!s2 && s1)
		return (str_dup(s1));
	if (!s1 && !s2)
		return (NULL);
	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	while (s1[i])
		str[j++] = s1[i++];
	i = 0;
	while (s2[i])
		str[j++] = s2[i++];
	str[j] = '\0';
	return (str);
}
int			str_cmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	if (!s1[i] && !s2[i])
		return (1);
	return (0);
}
t_env_list	*get_list_env(char **env)
{
	t_env_list	*new_env;
	t_env_list	*serch;
	
	int			i;
	
	i = 1;
	new_env = ft_lstnew(env[0]);
	while (env[i])
	{
		ft_lstadd_back(&new_env, ft_lstnew(env[i]));
		i++;
	}
	serch = new_env;
	while (serch)
	{
		if (str_cmp(serch->content.first, "OLDPWD"))
		{
			free(serch->content.last);
			serch->content.last = NULL;
		}
		serch = serch->next;
	}
	return (new_env);
}