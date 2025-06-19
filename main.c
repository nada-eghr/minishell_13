/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slamhaou <slamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 09:32:00 by slamhaou          #+#    #+#             */
/*   Updated: 2025/06/16 17:11:44 by slamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heder_shell.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define TYPE_IN 0
#define TYPE_OUT 1

// Create new redirection node
t_redirection *create_redirection(char *file, int type) {
	t_redirection *r = malloc(sizeof(t_redirection));
	r->file = strdup(file);
	r->type = type;
	r->next = NULL;
	return r;
}

// Create new command node
t_cmd *create_cmd() {
	t_cmd *cmd = malloc(sizeof(t_cmd));
	cmd->arg = NULL;
	cmd->redi = NULL;
	cmd->herdoc = 0;
	cmd->next = NULL;
	return cmd;
}

// Append redirection at the end
void add_redirection(t_cmd *cmd, t_redirection *redir) {
	if (!cmd->redi)
		cmd->redi = redir;
	else {
		t_redirection *tmp = cmd->redi;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = redir;
	}
}

// Naive space splitter
char **split_by_space(char *str, int *count) {
	char **tokens = malloc(sizeof(char *) * 256);
	char *token = strtok(str, " ");
	int i = 0;
	while (token) {
		tokens[i++] = strdup(token);
		token = strtok(NULL, " ");
	}
	tokens[i] = NULL;
	if (count) *count = i;
	return tokens;
}


t_cmd *smal_list(char *input) {
	t_cmd *head = NULL, *curr = NULL;
	char *token = strtok(input, "|");

	while (token) {
		t_cmd *node = create_cmd();
		int i, j = 0, count;
		char **parts = split_by_space(token, &count);
		node->arg = malloc(sizeof(char *) * (count + 1));

		for (i = 0; i < count; i++) {
			if (strcmp(parts[i], "<") == 0 && i + 1 < count) {
				add_redirection(node, create_redirection(parts[++i], TOKEN_REDIR_IN));
			} else if (strcmp(parts[i], ">") == 0 && i + 1 < count) {
				add_redirection(node, create_redirection(parts[++i], TOKEN_REDIR_OUT));
			} else if (strcmp(parts[i], ">>") == 0 && i + 1 < count) {
				add_redirection(node, create_redirection(parts[++i], TOKEN_APPEND));
			} else if (strcmp(parts[i], "<<") == 0 && i + 1 < count) {
				add_redirection(node, create_redirection(parts[++i], TOKEN_HERDOC));
				node->herdoc = 1;
			} else {
				node->arg[j++] = strdup(parts[i]);
			}
		}
		node->arg[j] = NULL;

		if (!head)
			head = node;
		else
			curr->next = node;
		curr = node;

		token = strtok(NULL, "|");
	}
	return head;
}


int main(int ac, char **av, char **env) 
{
	char *input;
	t_cmd *cmd_list;
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