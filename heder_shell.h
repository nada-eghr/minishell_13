/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heder_shell.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slamhaou <slamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:47:26 by slamhaou          #+#    #+#             */
/*   Updated: 2025/06/29 18:34:14 by slamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef HEDER_SHELL_H
# define HEDER_SHELL_H

//-----------INCLUDE-------------

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
#include <string.h>
#include <limits.h>
#include <fcntl.h>
#include <readline/readline.h>
#define	ERORR	-1
#define SUCCESS 0
#define NO_REDERCT -2 
#define CMD_NOTFIND 127
//-----------EXECUTION----------
//.
//			SAFIYA
//.
//------------------------------

//global//
extern int	exit_sta;
///
typedef struct data_env
{
	char	*first;
	char	*last;
}t_data;

typedef struct s_list
{
	t_data			content;
	struct s_list	*next;
}t_env_list;

//---------------------------  cmd struct  -------------------------------
typedef enum e_token_type 
{
		TOKEN_WORD, /* word */
		TOKEN_PIPE,          /* | */ 
		TOKEN_REDIR_IN,      /* < */
		TOKEN_REDIR_OUT,     /* > */
		TOKEN_APPEND,       /* >> */
		TOKEN_HERDOC,       /* << */
		TOKEN_ENV_VAR,      /* $.. */
		TOKEN_QUOTED,
		TOKEN_UNKNOWN
} t_token_type;

typedef struct s_redirection
{
	char					*file;
	int						type;
	struct s_redirection	*next;
}							t_redirection;

typedef struct s_cmd
{
	char					**arg;
	int 					herdoc; // 0 for no herdoc, 1 for herdoc
	t_redirection			*redi;
	struct s_cmd 			*next; // next command in pipeline
}							t_cmd;
//////// /////
typedef	struct variabel
{
	int		i;
	char	*path;
	char	*new_path;
	char	**split_path;
	int		last_in;
	int		last_out;
	int		sav_in;
	int		sav_out;
}t_var;


t_env_list	*get_list_env(char **env);
t_env_list	*ft_lstnew_env(void *content);
void		ft_lstadd_back(t_env_list **lst, t_env_list *new);
int			ft_strlen(char *str);
int			str_cmp(char *s1, char *s2);
char		**ft_split(char *str, char sep);
char		*str_join(char *s1, char *s2, char sep);
char		*str_dup(char *s);
void		free_tab(char **str);
char		*my_get_env(char *str, t_env_list *env);
char		**return_list_to_arg(t_env_list *list_env);
int			is_alpha(char c);
void	write_err(char *s, char *arg, char *last);
//////----BILT_IN----///////
int		my_pwd(void);
int		my_env(t_env_list *env);
int		my_cd(t_env_list *ev, char **arg);
int		my_unset(t_env_list **en, char **args);
int		my_export(t_env_list *env, char **args);
void		my_exit(char **args);
void	my_echo(char **args);
void	exc(t_cmd *list, t_env_list **list_env);
int		bilt_in(t_cmd *list, t_env_list **list_env); //hydeha ger katesty beha
///////////////////rediraction/////////////////
void	rederection(t_cmd *list, t_var *var);


# endif
