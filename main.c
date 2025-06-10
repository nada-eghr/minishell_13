/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slamhaou <slamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 09:32:00 by slamhaou          #+#    #+#             */
/*   Updated: 2025/06/10 10:13:59 by slamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heder_shell.h"


char **split_args(char *s) {
	int count = 0;
	char **result = malloc(sizeof(char *) * 100); 
	char *token = strtok(s, " ");
	while (token) {
		result[count++] = strdup(token);
		token = strtok(NULL, " ");
	}
	result[count] = NULL;
	return result;
}

t_my_list *smal_list(char *s)
{
	char	**split = split_args(s);
	t_my_list *list;
	int		i = 0, j = 0, out_i = 0;
	char	**args_clean = malloc(sizeof(char *) * 100);
	char	**out_files = malloc(sizeof(char *) * 100);

	if (!split)
		return NULL;

	while (split[i])
	{
		if (strcmp(split[i], ">") == 0 && split[i + 1])
		{
			out_files[out_i++] = strdup(split[i + 1]);
			i += 2;
		}
		else
		{
			args_clean[j++] = strdup(split[i]);
			i++;
		}
	}
	args_clean[j] = NULL;
	out_files[out_i] = NULL;

	list = malloc(sizeof(t_my_list));
	if (!list)
		return NULL;
	list->args = args_clean;
	list->outf = out_files;
	list->inf = NULL;
	list->next = NULL;
	
	int k = 0;
	while (split[k])
		free(split[k++]);
	free(split);

	return list;
}


int main(int ac, char **av, char **env) 
{
	char *input;
	t_my_list *cmd_list;
	t_env_list *e;
	int i;

	i = 0;
	ac = 0;
	av = NULL;
	e = get_list_env(env);
	input = "wee";
	while (input) 
	{
		input = readline("Minishell$ ");
		cmd_list = smal_list(input);
		exc(cmd_list, &e);
	}
	return 0;
}