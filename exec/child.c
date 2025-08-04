/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 13:06:30 by slamhaou          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/08/04 12:53:25 by naessgui         ###   ########.fr       */
=======
/*   Updated: 2025/08/04 10:55:07 by slamhaou         ###   ########.fr       */
>>>>>>> 66167f95af7cec6f4594e5494386c9cc6e1f7834
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	arr_id_pross(t_var *var, t_cmd *list)
{
	int	counter;

	counter = 0;
	while (list)
	{
		counter++;
		list = list->next;
	}
	if (counter == 0)
		return;
	var->num_cmd = counter;
	var->arr_id = malloc(sizeof(pid_t) * counter);
}

void	wait_child(t_var *var)
{
	int i;
	int	stat;

	i = 0;

	while (i < var->num_cmd)
	{
		waitpid(var->arr_id[i], &stat, 0);
		if (i == var->num_cmd - 1 && var->its_bilt == 0)
		{
			if (var->last_in != ERORR && var->last_out != ERORR)
				var->exit_stat =  WEXITSTATUS(stat);
		}
		i++;
	}
	free(var->arr_id);
}
void	h(int s)
{
	(void)s;
	exit(0);
}
void	my_child(t_var *var, t_cmd *list, t_env_list **list_env)
{
	char	**env_arr;
	char	*path;
	int		b;

<<<<<<< HEAD
	signal(SIGQUIT, h);
=======
	signal(SIGQUIT, SIG_DFL);
>>>>>>> 66167f95af7cec6f4594e5494386c9cc6e1f7834
	if (var->last_in == ERORR || var->last_out == ERORR)
	{
		close (var->pip_fd[1]);
		var->exit_stat = 1;
		exit (0);
	}
	if (var->rd_fd != NO_PIP)
	{
		if (var->rd_fd != FIRST_CMD)
		{
			dup2(var->rd_fd, 0);
			close(var->rd_fd);
		}
		if (var->i < var->num_cmd - 1)
		{
			dup2(var->pip_fd[1], 1);
			close(var->pip_fd[1]);
		}
	}
	if (var->last_in >= 0)
	{
		dup2(var->last_in, 0);
		close(var->last_in);
	}
	if (var->last_out >= 0)
	{
		dup2(var->last_out, 1);
		close(var->last_out);
	}
	b = bilt_in(var,list, &*list_env);
	if (b == 1)
		exit (var->exit_stat);
	path = it_correct_comnd(&var->exit_stat,list->arg[0], *list_env);
	if (!path)
		exit (var->exit_stat);
	env_arr = return_list_to_arg(*list_env);
	if (execve(path, list->arg, env_arr) < 0)
	{
		free_tab(env_arr);
		exit (127);
	}
}

