// #include"minishell.h"
// typedef struct s_list
// {
//     char *filename;
//     char *filetype;
//     struct s_list *next;

// }t_list;


// int count_outfile(t_token *tokens) 
// {
//     t_token *curr = tokens;
//     int count = 0;
//     while (curr->type != TOKEN_PIPE)
//     {
//         if ((curr->type == TOKEN_REDIR_OUT || curr->type == TOKEN_APPEND) && curr->next)
//             count++;

//         curr = curr->next;   
//     }  
//     return count;   
// }

//----------------------------------
//  typedef struct s_cmd
// {
// 	char **arg;
// 	char **infile;    // file after < 
// 	char **outfile;     // file after > 
// 	char **append; // file after >>
// 	char **herdoc; // file after <<
// 	struct s_cmd *next; // next command in pipeline

// }t_cmd;
    
// t_cmd *creat_cmd(t_token *list)
// {
//     t_cmd *cmd = (t_cmd*)malloc(sizeof(t_cmd));
//     if (!cmd)
//         return NULL;
//     cmd->arg = get_args(list);
//     cmd->infile = get_infiles(list);
//     cmd->append = get_append_files(list);
//     cmd->outfile = get_outfiles(list);
//     cmd->herdoc = get_herdoc_files(list);
//     cmd->next = NULL;
//     return (cmd);
// }
// t_cmd *list_cmd(t_token *tokens) 
// {
//     t_cmd *cmd = NULL;
//     t_token *curr = tokens;
//     t_token *prev ;

//     cmd = creat_cmd(curr);
//     add_back(curr);
//     prev = curr;
//     curr = curr->next;
//     while(curr)
//     {
       
//         // khdmi awl node bo7da

//         if  (prev->type == TOKEN_PIPE)
//         {
//               cmd = creat_cmd(curr);
//               add_back(cmd);
       
//         }
//         prev = tmp;
//        curr = curr->next; 
//     }
    
// }