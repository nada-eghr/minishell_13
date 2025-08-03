/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_gvalue.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 13:31:03 by naessgui          #+#    #+#             */
/*   Updated: 2025/08/02 13:15:52 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*joined;

	joined = ft_strjoin(s1, s2);
	free(s1);
	return (joined);
}

char	*handle_digit_env(const char *str, int *i, t_env_list *env, char *s)
{
	char		buf[2];
	t_env_list	*tmp;
	char		*temp;

	if (!isdigit(str[*i]))
		return (s);
	buf[0] = str[*i];
	buf[1] = '\0';
	(*i)++;
	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->content.key, buf, 2) == 0)
		{
			temp = ft_strjoin(s, tmp->content.value);
			free(s);
			return (temp);
		}
		tmp = tmp->next;
	}
	return (s);
}
