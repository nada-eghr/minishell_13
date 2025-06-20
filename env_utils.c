/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:58:33 by naessgui          #+#    #+#             */
/*   Updated: 2025/06/18 19:31:21 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char	*get_line(char *data, char c)
{
	int	i;
	int	j;
	char	*line;

	i = 0;
	j = 0;
	while (data[i] && data[i] != '=')
		i++;
	if (c == 'f')
	{
		line = malloc(i + 1);
		while (j < i)
		{
			line[j] = data[j];
			j++;
		}
		line[j] = '\0';
		return(line);
	}
	else if (data[i] && c == 'l')
	{
		if (data[i] == '=')
			i++;
		line = malloc(ft_strlen(&data[i]) + 1);
		while (data[i])
			line[j++] = data[i++];
		line[j] = '\0';
		return(line);
	}
	return (NULL);
}

t_env_list	*ft_lstnew_env(void *content)
{
	t_env_list	*nod;
	char	*key;
	char	*value;

	key = get_line(content, 'f');
	value = get_line(content, 'l');
	nod = malloc(sizeof(t_env_list));
	if (!nod)
		return (NULL);
	nod->content.key = key;
	nod->content.value = value;
	nod->next = NULL;
	return (nod);
}

void	ft_lstadd_back(t_env_list **lst, t_env_list *n)
{
	t_env_list	*list;

	if (!lst || !n)
		return ;
	list = *lst;
	if (*lst == NULL)
	{
		*lst = n;
		return ;
	}
	while (list->next)
		list = list->next;
	list->next = n;
}
char	*my_get_env(char *str, t_env_list *env)
{

	while (env)
	{
		if (ft_strcmp(str, env->content.key))
			return (env->content.value);
		env = env->next;	
	}
	return (NULL);
}
t_env_list	*get_list_env(char **env)
{
	t_env_list	*new_env;
	t_env_list	*serch;
	int			i;
	int			serch_old_p;
	
	i = 1;
	new_env = ft_lstnew_env(env[0]);
	serch_old_p = 0;
	while (env[i])
	{
		ft_lstadd_back(&new_env, ft_lstnew_env(env[i]));
		i++;
	}
	serch = new_env;
    // why the oldpwd is null
	while (serch)
	{
		if (!ft_strcmp(serch->content.key, "OLDPWD"))
		{
			free(serch->content.value);
			serch->content.value = NULL;
			serch_old_p = 1;
		}
		serch = serch->next;
	}
	if (serch_old_p == 0)
		ft_lstadd_back(&new_env, ft_lstnew_env("OLDPWD"));
	return (new_env);
}