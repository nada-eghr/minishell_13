/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:35:55 by naessgui          #+#    #+#             */
/*   Updated: 2025/06/12 20:05:32 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"


void print_args(t_cmd *node_cmd)
{
	int i = 0;
	t_cmd *tmp = node_cmd;
    printf("args    : [");
	while ( tmp->arg[i])
	{
		printf("%s , ", tmp->arg[i]);
		i++;
	}
    printf(" %s ", tmp->arg[i]);
    printf("]\n");
	// printf("\n");
}
void print_infile(t_cmd *node_cmd)
{
	int i = 0;
	t_cmd *tmp = node_cmd;
    printf("infile  : [");
	while ( tmp->infile[i])
	{
		printf("%s, ", tmp->infile[i]);
		i++;
	}
    printf("%s", tmp->infile[i]);
    printf("]\n");
	// printf("\n");
}
void print_outfile(t_cmd *node_cmd)
{
	int i = 0;
	t_cmd *tmp = node_cmd;
    printf("outfile : [");
	while ( tmp->outfile[i])
	{
		printf("%s , ", tmp->outfile[i]);
		i++;
	}
    printf("%s", tmp->outfile[i]);
     printf("]\n");
	// printf("\n");
}
void print_append(t_cmd *node_cmd)
{
	int i = 0;
	t_cmd *tmp = node_cmd;
    printf("append  : [");
	while ( tmp->append[i])
	{
		printf("%s , ", tmp->append[i]);
		i++;
	}
    printf("%s ", tmp->append[i]);
     printf("]\n");
	// printf("\n");
}
void print_herdoc(t_cmd *node_cmd)
{
	int i = 0;
	t_cmd *tmp = node_cmd;
    printf("herdoc  : [");
	while ( tmp->herdoc[i])
	{
		printf("%s , ", tmp->herdoc[i]);
		i++;
	}
    printf("%s ", tmp->herdoc[i]);
    printf("]\n");
	// printf("\n");
}
void printcmdLinkedList(t_cmd* head)
{
    t_cmd* current = head;
    int i = 0;
    while (current != NULL) {
        printf("cmd[%d]\n",i);
        // printf("%s -> ", current->token);
		print_args(current);
        print_outfile(current);
        print_infile(current);
        print_append(current);
        print_herdoc(current);
        printf("\n");
        current = current->next;
        i++;
    }
    // printf("NULL\n");
}