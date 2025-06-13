
#include "minishell.h"

// cmd->args = get_argsetre(t_token);

int count_args(t_token *list)
{
    int count = 0;
    t_token *tmp = list;
    t_token *prev ;
    

    if(tmp->type == TOKEN_WORD || tmp->type == TOKEN_QUOTED)
        count++;
    prev = tmp;
    tmp = tmp->next;
    while (tmp && tmp->type != TOKEN_PIPE) 
    {
        if (( prev->type == TOKEN_PIPE || prev->type == TOKEN_WORD  || prev->type == TOKEN_QUOTED) && (tmp->type == TOKEN_WORD || tmp->type == TOKEN_QUOTED))
            count++;
        
        prev = tmp ;
        tmp = tmp->next;
    }
    return count ;
}

char **get_args(t_token *token)
{
    t_token *tmp = token;
    t_token *prev ;
    int i = 0;
    int count = count_args(token);
    char **cmd = malloc(sizeof(char*) * (count+2));
    if (!*cmd)
        return NULL;
    if(tmp->type == TOKEN_WORD){
         cmd[i] = strdup(tmp->token);
        // printf("cmd[%d] = %s\n",i,cmd[i]);
        i++;
    }
    // printf("cmd[%d],%s\n",i,cmd[i]);
    
    prev = tmp;
    tmp = tmp->next;
    while (tmp && tmp->type != TOKEN_PIPE) 
    {
        if (( prev->type == TOKEN_PIPE || prev->type == TOKEN_WORD  || prev->type == TOKEN_QUOTED) && (tmp->type == TOKEN_WORD || tmp->type == TOKEN_QUOTED))
        {
            
            cmd[i] = strdup(tmp->token);
            // printf("cmd[%d],%s\n",i,cmd[i]);
            i++;
        }
        prev = tmp ;
        tmp = tmp->next;
    }
    cmd[i] = NULL;
    return (cmd);
}
// int count_infiles(t_token *list)
// {
//     int count = 0;
//     t_token *tmp = list;
//     t_token *prev;
    
//     prev = tmp;
//     tmp = tmp->next;
//     while (tmp && tmp->type != TOKEN_PIPE)
//     {
//         if ((prev->type == TOKEN_REDIR_IN) && (tmp->type == TOKEN_WORD || tmp->type == TOKEN_QUOTED))
//             count++;
//         prev = tmp;
//         tmp = tmp->next;
//     }
//     return count;


// }

   
// char **get_infile(t_token *token)
// {
//     t_token *tmp =token;
//     t_token *prev;
//     int i = 0;
//     int count = count_infile(token);
//     char **infiles = malloc(sizeof(char *) * (count + 2));
//     if (!*infiles)
//         return NULL;
//     prev = tmp;
//     tmp = tmp->next;
//     while (tmp && tmp->type != TOKEN_PIPE) 
//     {
//         if (( prev->type == TOKEN_REDIR_IN) && (tmp->type == TOKEN_WORD || tmp->type == TOKEN_QUOTED))
//         {
            
//             infiles[i] = strdup(tmp->token);
//             // printf("infiles[%d],%s\n",i,infiles[i]);
//             i++;
//         }
//         prev = tmp ;
//         tmp = tmp->next;
//     }
//     infiles[i] = NULL;
//     return (infiles);   
// }   
