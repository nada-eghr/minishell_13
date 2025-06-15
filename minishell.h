/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 20:55:34 by naessgui          #+#    #+#             */
/*   Updated: 2025/06/15 10:51:41 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <ctype.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

//---------------------------------------------------------
typedef enum e_token_type
{
	TOKEN_WORD,      
	TOKEN_PIPE,      /* | */
	TOKEN_REDIR_IN,  /* < */
	TOKEN_REDIR_OUT, /* > */
	TOKEN_APPEND,    /* >> */
	TOKEN_HERDOC,    /* << */
	TOKEN_ENV_VAR,   /* $.. */
	TOKEN_QUOTED,
	TOKEN_UNKNOWN
}							t_token_type;

typedef struct s_token
{
	char					*token;
	t_token_type			type;
	struct s_token			*next;

}							t_token;
//---------------------------  cmd struct  -------------------------------
typedef struct s_redirection
{
	char					*file;
	int						type;
	struct s_redirection	*next;
}							t_redirection;

typedef struct s_cmd
{
	char					**arg;
	int herdoc; // 0 for no herdoc, 1 for herdoc
	t_redirection			*redi;
	struct s_cmd *next; // next command in pipeline
}							t_cmd;
//-----------------------    check_syntaxe    -----------------------------

bool						check_pipe(t_token **list);
bool						check_unclosed_quotes(t_token *tokens);
bool						check_redirections(t_token **list);
bool						check_error(t_token **list);
//-------------------------      cmd        -------------------------------

t_cmd						*creat_cmd(t_token *list);
void						add_back_cmd(t_cmd **head, t_cmd *node);
t_cmd						*list_cmd(t_token *tokens);
void						print_cmd(t_cmd *node_cmd);

//-------------------------    get_files     ------------------------------

t_redirection				*add_new(int type, char *file_name);
void						ft_add_back_redi(t_redirection **head,
								t_redirection *node);
t_redirection				*get_files(t_token *token);

//--------------------------    get_param    ------------------------------

int							count_args(t_token *list);
char						**get_args(t_token *token);

// ---------------------------- herdoc ------------------------------------

int							check(t_token *token);

//---------------------------  listUtils  ---------------------------------

t_token						*creattoken(char *data);
void						add_back(t_token **head, t_token *node);
void						printlinkedlist(t_token *head);
void						print_node_cmd(t_cmd *node_cmd);
void						free_list(t_token *head);

//--------------------------   tokenization  ------------------------------

t_token_type				get_token_type(char *token);
t_token						*convert_to_node(char *data);
int							ft_isprint(int c);

// void ll();

//--------------------------    utils    ----------------------------------

int							ft_strcmp(char *s1, char *s2);
int							ft_strlen(char *str);
char						*ft_strncpy(char *dst, const char *src, size_t n);
char						*substr(const char *src, int start, int len);
char						*ft_strdup(char *s);
//--------------------------    utils1    ----------------------------------
int							ft_isprint(int c);
int							ft_space(char c);

#endif