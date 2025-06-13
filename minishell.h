/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 20:55:34 by naessgui          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/06/13 15:51:53 by naessgui         ###   ########.fr       */
=======
/*   Updated: 2025/06/12 18:56:31 by naessgui         ###   ########.fr       */
>>>>>>> 05a0283f39f744cb5e626e050f696d346ca0144c
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

<<<<<<< HEAD
//#include <filesystem>
=======
>>>>>>> 05a0283f39f744cb5e626e050f696d346ca0144c
#include<stdio.h>
#include<stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <readline/readline.h>

//---------------------------------------------------------
typedef enum e_token_type 
{
		TOKEN_WORD,
		TOKEN_PIPE,          /* | */ 
		TOKEN_REDIR_IN,      /* < */
		TOKEN_REDIR_OUT,     /* > */
		TOKEN_APPEND,        /* >> */
		TOKEN_HERDOC,       /* << */
		TOKEN_ENV_VAR,      /* $.. */
		TOKEN_QUOTED,
		TOKEN_UNKNOWN
} t_token_type;

<<<<<<< HEAD
typedef struct s_rediraction
{
	char *file; // file name after <, >, >>, <<
	int type; // 0 for <, 1 for >, 2 for >>, 3 for <<
} t_rediraction;
=======
>>>>>>> 05a0283f39f744cb5e626e050f696d346ca0144c

typedef struct s_token
{
	char *token;
	int quoted; // 1 if quoted, 0 if not
	t_token_type type;
	struct s_token *next;
	
} t_token;
<<<<<<< HEAD
//---------------------------  infiles struct  ---------------------------------
typedef struct s_infiles
{
	char **infiles; // array of infile names
	int *infile_flag; // 0 for <, 1 for << , -1 for no infile
	
}t_infiles;
//---------------------------  outfiles struct  ---------------------------------

typedef struct s_outfiles
{
	char **outfiles; // array of outfile names
	int *outfile_flag; // 0 for >, 1 for >>, -1 for no outfile
} t_outfiles;

=======
>>>>>>> 05a0283f39f744cb5e626e050f696d346ca0144c
//---------------------------  cmd struct  ---------------------------------
 typedef struct s_cmd
{
	char **arg;
<<<<<<< HEAD
	t_infiles *infile; // struct for infile names and flags
	t_outfiles *outfile; // struct for outfile names and flags
	char **herdoc; // file after <<
	struct s_cmd *next; // next command in pipeline


	
	//char **infile;    // file after < 
	//char **outfile;     // file after > && >> 
	//char **append; // file after >>
	
	//int *outfile_flag; // 0 for >, 1 for >>, -1 for no outfile
	//int *infile_flag; // 0 for <, 1 for << , -1 for no infile

=======
	char **infile;    // file after < 
	char **outfile;     // file after > 
	char **append; // file after >>
	char **herdoc; // file after <<
	struct s_cmd *next; // next command in pipeline

>>>>>>> 05a0283f39f744cb5e626e050f696d346ca0144c
}t_cmd;
	//int count_append;         // 1 for >>, 0 for >3

////////////////EWWWWWWWWWW//////////////
bool check_pipe(t_token** list);
bool check_error(t_token **list);
bool check_redirections(t_token**list);



//---------------------------  listUtils  ---------------------------------

t_token* creattoken(char *data);
void	add_back(t_token **head, t_token *node);
void printLinkedList(t_token* head);
void free_list(t_token *head);

//--------------------------    utils    -----------------------------------

int ft_strcmp(char *s1, char *s2);
int ft_strlen(char *str);
char *substr(const char *src, int start, int len);
int			ft_space(char c);

//--------------------------   tokenization  -------------------------------
t_token_type get_token_type(char *token);
t_token *convert_to_node(char *data);
void ll();
// /

// int count_outfile(t_token *tokens) ;
int count_args(t_token *list);
char **get_args(t_token *token);
int count_infiles(t_token *list);
char **get_infiles(t_token *token);
char **get_outfiles(t_token *token);
int count_outfiles(t_token *list);
char **get_herdoc_files(t_token *token);
int count_herdoc_files(t_token *list);
int count_append_files(t_token *list);
char **get_append_files(t_token *token);

//----------------------------------------

t_cmd *creat_cmd(t_token *list);
void	add_back_cmd(t_cmd **head, t_cmd *node);
t_cmd *list_cmd(t_token *tokens);
void printcmdLinkedList(t_cmd* head);
<<<<<<< HEAD
int *outfiles_flage(t_token *token);

int count_out_arr(t_token *list);
int *infiles_flage(t_token *token);
int count_in_arr(t_token *list);
void print_infile_flage(t_cmd *node_cmd);
=======


>>>>>>> 05a0283f39f744cb5e626e050f696d346ca0144c
#endif
//     char **cmd;          // main command (like "ls")
//     char **infile;    // file after <
//     char **outfile;     // file after > or >>
// 	char **heredoc;
//     int count_append;         // 1 for >>, 0 for >

//     struct s_cmd *next; // next command in pipeline
// } t_cmd;

// data->cmd = NULL; // main command (like "ls")


////////////////SAFFFIAA//////////
// typedef struct data 
// {
// 	char *first;
// 	char *last;
// } t_data;
// typedef struct list_env
// {
// 	t_data *data;
// 	struct list_env *next;
// } t_list;
// ---------------- old struct 
// typedef struct s_all
// {
//     char	*cmd;
//     char	**args;
//     t_file;
//     t_input input_output output_file;
//     struct s_all *next; 
	
// }t_all;