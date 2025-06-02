/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slamhaou <slamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 18:57:49 by slamhaou          #+#    #+#             */
/*   Updated: 2025/05/26 19:01:42 by slamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../heder_shell.h"

int	write_erorr(char *str, char *var)
{
	int	i;

	i = 0;
	while (str[i])
		write(2, &str[i++], 1);
	if (var)
	{
		write(2, "`",1);
		write(2, var, ft_strlen(var));
		write(2, "'", 1);
		write(2, ":", 1);
	}
	return (1);
}
int	chake_arg(char *str)
{
	int	i;

	i = 0;
	if (str[i] <= '9' && str[i] >= '0')
		return (1);
	while (str[i])
	{
		if (!(str[i] >= 'a' && str[i] <= 'z') && !(str[i] >= 'A' && str[i] <= 'Z'))
			if (str[i] != '_')
				return (1);
		i++;
	}
	return (0);
}
void	delet_list(t_env_list **en, char *var)
{
	t_env_list *first;
	t_env_list *therd;
	t_env_list	*env;
	int start;
	
	start = 0;
	env = *en;
	first = env;
	while (env && str_cmp(env->content.first, var) == 0)
	{
		env = env->next;
		start++;
	}
	while (first && first->next != env)
		first = first->next;
	if (env)
	{
		therd = env->next;
		env->next = NULL;
		free(env->content.first);
		free(env->content.last);
		free(env);
		if (first)
			first->next = therd;
		if (start == 0)
			*en = therd;
	}
}

int	my_unset(t_env_list **en, char **args)
{
	int			i;
	int			ret;
	
	i = 1;
	ret = 0;
	while (args[i])
	{
		if (chake_arg(args[i]))
		{
			write_erorr("Minishell: unset: ", args[i]);
			write_erorr(" not a valid identifier\n", NULL);
			ret = 1;
		}
		delet_list(en, args[i]);
		i++;
	}
	return (ret);
}
