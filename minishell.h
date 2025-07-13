/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 20:55:34 by naessgui          #+#    #+#             */
/*   Updated: 2025/07/13 11:25:07 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <ctype.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# define ERORR -1
# define NO_REDERCT -2
# define FIRST_CMD -3
# define NO_PIP -4
# define SUCCESS 1
# define CMD_NOTFIND 127

//---------------------------------------------------------
typedef struct variabel
{
	int						i;
	int						rd_fd;
	int						last_in;
	int						last_out;
	int						id_pros;
	int						exit_stat;
	int						*arr_id;
	int						num_cmd;
	int						pip_fd[2];
}							t_var;
typedef struct p_var
{
	bool					s_quote;
	bool					d_quote;
	char					*input_line;

}							t_p_var;

typedef enum e_token_type
{
	T_WORD,
	T_PIPE,    /* | */
	T_RED_IN,  /* < */
	T_RED_OUT, /* > */
	T_APPEND,  /* >> */
	T_HEREDOC, /* << */
	T_ENV,     /* $.. */
	T_S_QUOTE, /* '...' */
	T_D_QUOTE, /* "..." */
	T_UNKNOWN,
	T_SPACE
}							t_token_type;

typedef struct s_token
{
	char					*token;
	t_token_type			type;
	struct s_token			*next;
	bool					is_quoted;
}							t_token;

typedef struct s_second_token
{
	char					*token;
	t_token_type			type;
	struct s_second_token	*next;
}							t_second_token;

//---------------------------  cmd struct  -------------------------------
typedef struct s_redirection
{
	char					*file;
	int						type;
	int						her_doc;
	struct s_redirection	*next;
}							t_redirection;

typedef struct s_cmd
{
	char					**arg;
	t_redirection			*redi;
	struct s_cmd *next; // next command in pipeline
}							t_cmd;

//---------------------------  env struct  -------------------------------

typedef struct data_env
{
	char					*key;
	char					*value;
}							t_data;

typedef struct s_list
{
	t_data					content;
	struct s_list			*next;
}							t_env_list;

//-----------------------    check_syntaxe    -----------------------------

bool						check_error(t_second_token **list);
bool						check_error2(t_token **list);
//-------------------------      cmd        -------------------------------

t_cmd						*creat_cmd(t_second_token *list);
void						add_back_cmd(t_cmd **head, t_cmd *node);
t_cmd						*list_cmd(t_second_token *tokens);
void						print_node_cmd(t_cmd *node_cmd);
void						print_cmd(t_cmd *node_cmd);

//-------------------------  expand_utils  --------------------------------

int							ft_strncmp(const char *s1, const char *s2,
								size_t n);
char						*ft_itoa(int n);
void						ft_free_exp(char *s1, char *s2, char *s3);
int							is_end_of_key(char c);

//---------------------------	expand    ------------------------------

void						expand_env_token(t_token *tmp, t_env_list *env,
								int *exit_stat);
void						expand_double_quote(t_token *tmp, t_env_list *env,
								int *exit_stat);
void						expand_single_quote(t_token *tmp);
void						expand_word_token(t_token *tmp, t_env_list *env,
								int *exit_stat);
t_token						*expand_token(t_token *token, t_env_list *env,
								int *exit_stat);

//-------------------------  expand1  --------------------------------

void						skip_quoted_text(char *str, int *i, char **s);
char						*join_empty_and_skip(char *str, int *i, char *s);
char						*get_env_or_empty(char *key, t_env_list *env,
								int *exit_stat);
void						expand_env_variable(t_token *tmp, t_env_list *env,
								int *exit_stat);
void						remove_quotes(t_token *tmp);

//----------------------------- filter_token -----------------------------

void						delete_specific_node(t_token **head,
								t_token *nodeToDelete);
t_token						*convert_to_token(t_token *token);

//-------------------------    get_files     ------------------------------

t_redirection				*add_new(int type, char *file_name, int her_doc);
void						ft_add_back_redi(t_redirection **head,
								t_redirection *node);
t_redirection				*get_files(t_second_token *token);

//--------------------------    get_param    ------------------------------

int							count_args(t_second_token *list);
char						**get_args(t_second_token *token);

//-------------------------  get_value  ----------------------------------

char						*handle_special_dollar(char *s, int *i,
								int *exit_stat);
char						*extract_var_value(char *str, int *i,
								t_env_list *env, char *s);
char						*handle_empty_or_space_after_dollar(char *s, int *i,
								char next);
char						*append_char_to_str(char *s, char c);
char						*get_value1(char *str, t_env_list *env,
								int *exit_stat);

//---------------------------  listUtils  ---------------------------------

t_token						*creattoken(char *data);
void						add_back(t_token **head, t_token *node);
void						printlinkedlist(t_token *head);
void						free_list(t_token *head);

//--------------------------lst_Utils1-------------------------------

t_second_token				*creat_second_token(char *data, t_token_type type);
void						add_b(t_second_token **head, t_second_token *node);
void						printlinkedlist1(t_second_token *head);
void						free_list1(t_second_token *head);

//--------------------------    pars.c   ----------------------------------

t_token						*parse_operator_token(const char *data, int *i);
t_token						*parse_quoted_token(const char *data, int *i);
t_token						*parse_word_token(const char *data, int *i);
t_token						*handle_spaces(const char *data, int *i);
t_token						*handle_quotes(const char *data, int *i);

//---------------------------  quotes  ---------------------------------

int							check_quotes(char *str);

//------------------------ second_tokinization -----------------------------

t_second_token				*second_tokinization(t_token *token);

//--------------------------   tokenization  ------------------------------

t_token_type				get_token_type(char *token);
t_token						*convert_to_node(char *data);

//--------------------------    utils    ----------------------------------

int							ft_strcmp(char *s1, char *s2);
int							ft_strlen(char *str);
char						*ft_strncpy(char *dst, const char *src, size_t n);
char						*substr(const char *src, int start, int len);
char						*ft_strdup(char *s);

//--------------------------    utils1    ----------------------------------

int							ft_isprint(int c);
int							ft_space(char c);
char						*ft_strjoin(char *s1, char *s2);
char						*ft_strchr(char *s, int c);
bool						is_line_empty(const char *line);

//–----------------------------------------------------------------------------

// void ll();
// char *expand_line(char *input , t_env_list *env_list);

///////////////////////////////exc/////////////////////////////////////////

//-----------------------------------------
t_env_list					*get_list_env(char **env);
t_env_list					*ft_lstnew_env(void *content);
void						ft_lstadd_back(t_env_list **lst, t_env_list *n);
int							ft_strlen(char *str);
int							str_cmp(char *s1, char *s2);
char						**ft_split(char *str, char sep);
char						*str_join(char *s1, char *s2, char sep);
char						*str_dup(char *s);
void						free_tab(char **str);
char						*my_get_env(char *str, t_env_list *env);
char						**return_list_to_arg(t_env_list *list_env);
int							is_alpha(char c);
void						write_err(char *s, char *arg, char *last);
char						*it_correct_comnd(int *exit_st, char *cmd,
								t_env_list *env);
//////----BILT_IN----///////
void						my_pwd(int *exit_sta);
void						my_env(t_env_list *env, int *exit_st);
void						my_cd(t_env_list *env, char **arg, int *exit_st);
int							my_unset(t_env_list **en, char **args);
int							my_export(t_env_list *env, char **args);
void						my_exit(char **args, int *exit_st);
void						my_echo(char **args, int *exit_st);
void						exc(t_cmd *list, t_env_list **list_env);
int	bilt_in(int *exit_st, t_cmd *list, t_env_list **list_env);
		// hydeha ger katesty beha
///////////////////rediraction/////////////////
void						rederection(t_cmd *list, t_var *var);

#endif