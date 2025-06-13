/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 10:56:04 by naessgui          #+#    #+#             */
/*   Updated: 2025/06/13 12:18:22 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_cmd *lst_cmd(t_token *list)
// {
//     t_cmd *cmd = (t_cmd*)malloc(sizeof(t_cmd));
//     if (!cmd)
//         return NULL;
//     cmd->arg = NULL;
//     cmd->infile = NULL;
//     cmd->append = NULL;
//     cmd->outfile = NULL;
//     cmd->herdoc = NULL;
//     cmd->next = NULL;
//     return (cmd);
// }
void free_str_array(char **arr)
{
	if (!arr)
		return;
	for (int i = 0; arr[i]; i++)
		free(arr[i]);
	free(arr);
}

void free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return;
	free_str_array(cmd->arg);
	free_str_array(cmd->infile);
	free_str_array(cmd->outfile);
	//free_str_array(cmd->append);
	free_str_array(cmd->herdoc);
	free(cmd);
}

t_cmd **remplir_cmd(t_token *list)
{
    t_token *tmp = list;
    
    while ( tmp != NULL)
    {
        while (tmp->type != TOKEN_PIPE){
            
        }
            
        tmp=tmp->next;
    }
    
    
         
    // return arr;
    
}
// t_cmd **remplir_cmd(t_token **list)
// {
//     t_token *tmp = *list;
//     while (tmp)
//     {
//         if (tmp->type == TOKEN_WORD)
//         tmp = tmp->next;
//     }
// }
char **add_str_to_array(char **arr , char *new_str)
{
    char **new_arr;
    int count = 0;
    
    while (arr && arr[count])
        count++;
}
//  typedef struct s_cmd
// {
// 	char **arg;
// 	char **infile;    // file after < 
// 	char **outfile;     // file after > 
// 	char **append; // file after >>
// 	char **herdoc; // file after <<
// 	struct s_cmd *next; // next command in pipeline

// }t_cmd;
// t_cmd *lst_cmd(t_token *list)