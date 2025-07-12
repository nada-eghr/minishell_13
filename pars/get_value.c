/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:38:46 by naessgui          #+#    #+#             */
/*   Updated: 2025/07/12 14:47:59 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*handle_special_dollar(char *s, int *i , int *exit_stat)
{
	char	*status;
	char	*temp;


	status = ft_itoa(*exit_stat);
	temp = ft_strjoin(s, status);
	free(s);
	free(status);
	*i += 2;
	return (temp);
}

char	*extract_var_value(char *str, int *i, t_env_list *env, char *s)
{
	t_env_list	*tmp;
	char		*temp;
	int			found;

	found = 0;
	tmp = env;
	if (str[*i] == '\'' || str[*i] == '"')
		skip_quoted_text(str, i, &s);
	while (tmp)
	{
		if (!ft_strncmp(&str[*i], tmp->content.key, ft_strlen(tmp->content.key))
			&& is_end_of_key(str[*i + ft_strlen(tmp->content.key)]))
		{
			found = 1;
			temp = ft_strjoin(s, tmp->content.value);
			free(s);
			s = temp;
			*i += ft_strlen(tmp->content.key);
			break ;
		}
		tmp = tmp->next;
	}
	if (!found)
		s = join_empty_and_skip(str, i, s);
	return (s);
}

char	*handle_empty_or_space_after_dollar(char *s, int *i, char next)
{
	char	*temp;

	temp = NULL;
	if (next == '$')
		temp = ft_strjoin(s, "$");
	else if (next == '?')
		temp = ft_strjoin(s, "?");
	free(s);
	(*i)++;
	return (temp);
}

char	*append_char_to_str(char *s, char c)
{
	char	*temp;
	char	buf[2];

	buf[0] = c;
	buf[1] = '\0';
	temp = ft_strjoin(s, buf);
	free(s);
	return (temp);
}

char	*get_value1(char *str, t_env_list *env,int *exit_stat)
{
	int		i;
	char	*s;

	i = 0;
	s = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$' && (str[i + 1] == '$' || str[i + 1] == '?'))
			s = handle_special_dollar( s, &i, exit_stat);
		else if (str[i] == '$' && (isalpha(str[i + 1]) || str[i + 1]))
		{
			i++;
			s = extract_var_value(str, &i, env, s);
		}
		else if (str[i] == '$' && (str[i + 1] == '\0' || str[i + 1] == ' '))
			s = handle_empty_or_space_after_dollar(s, &i, '$');
		else if (str[i] == '?' && (str[i + 1] == '\0' || str[i + 1] == ' '))
			s = handle_empty_or_space_after_dollar(s, &i, '?');
		else
			s = append_char_to_str(s, str[i++]);
	}
	return (s);
}
