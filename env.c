/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:44:31 by naessgui          #+#    #+#             */
/*   Updated: 2025/06/13 14:54:25 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
 typedef struct data_env
{
	char	*first;
	char	*last;
}t_data;

typedef struct s_list
{
	t_data			content;
	struct s_list	*next;
}t_env_list;

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
	char	*frst;
	char	*last;

	frst = get_line(content, 'f');
	last = get_line(content, 'l');
	nod = malloc(sizeof(t_env_list));
	if (!nod)
		return (NULL);
	nod->content.first = frst;
	nod->content.last = last;
	nod->next = NULL;
	return (nod);
}

void	ft_lstadd_back(t_env_list **lst, t_env_list *new)
{
	t_env_list	*list;

	if (!lst || !new)
		return ;
	list = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (list->next)
		list = list->next;
	list->next = new;
}
char	*my_get_env(char *str, t_env_list *env)
{

	while (env)
	{
		if (strcmp(str, env->content.first))
			return (env->content.last);
		env = env->next;	
	}
	return (NULL);
}