/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 18:35:55 by naessgui          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/06/13 15:49:00 by naessgui         ###   ########.fr       */
=======
/*   Updated: 2025/06/12 20:05:32 by naessgui         ###   ########.fr       */
>>>>>>> 05a0283f39f744cb5e626e050f696d346ca0144c
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
<<<<<<< HEAD
	while ( tmp->infile->infiles[i])
	{
		printf("%s, ", tmp->infile->infiles[i]);
		i++;
	}
    printf("%s", tmp->infile->infiles[i]);
=======
	while ( tmp->infile[i])
	{
		printf("%s, ", tmp->infile[i]);
		i++;
	}
    printf("%s", tmp->infile[i]);
>>>>>>> 05a0283f39f744cb5e626e050f696d346ca0144c
    printf("]\n");
	// printf("\n");
}
void print_outfile(t_cmd *node_cmd)
{
	int i = 0;
	t_cmd *tmp = node_cmd;
    printf("outfile : [");
<<<<<<< HEAD
	while ( tmp->outfile->outfiles[i])
	{
		printf("%s , ", tmp->outfile->outfiles[i]);
		i++;
	}
    printf("%s", tmp->outfile->outfiles[i]);
     printf("]\n");
	// printf("\n");
}
void print_outfile_flage(t_cmd *node_cmd)
{
	int i = 0;
	t_cmd *tmp = node_cmd;
    printf("outfiles_flag : [");
	while ( tmp->outfile->outfile_flag[i] != -1)
	{
		printf("%d , ", tmp->outfile->outfile_flag[i]);
		i++;
	}
    printf("%d ", tmp->outfile->outfile_flag[i]);
     printf("]\n");
	// printf("\n");
}
void print_infile_flage(t_cmd *node_cmd)
{
	int i = 0;
	t_cmd *tmp = node_cmd;
    printf("infiles_flag : [");
	while ( tmp->infile->infile_flag[i] != -1)
	{
		printf("%d , ", tmp->infile->infile_flag[i]);
		i++;
	}
    printf("%d ", tmp->infile->infile_flag[i]);
    printf("]\n");
	// printf("\n");
}

=======
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
>>>>>>> 05a0283f39f744cb5e626e050f696d346ca0144c
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
<<<<<<< HEAD
        print_outfile_flage(current);
		print_infile_flage(current);
=======
        print_append(current);
>>>>>>> 05a0283f39f744cb5e626e050f696d346ca0144c
        print_herdoc(current);
        printf("\n");
        current = current->next;
        i++;
    }
    // printf("NULL\n");
}