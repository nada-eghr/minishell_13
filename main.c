/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:27:48 by naessgui          #+#    #+#             */
/*   Updated: 2025/06/15 10:33:16 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int main() {
//      atexit(ll);
//     while(1)
//     {char *input = readline("minishell$");
//     t_token *tokens = convert_to_node(input);
//     if(!tokens)
//     {
//         free(tokens);
//         return (0);
//     }
//     if (check_error(&tokens) == 1)
//     {
//        // printf("minishell : syntax error"); /*free*/
//         free_list(tokens);
//         return (0);
//     }
//     // t_cmd *cmd = convert_to_cmd(&tokens)
//     //------------
//     t_token *current = tokens;

//     while (current) {
//         printf("{token -> %s } ", current->token);
//         printf("{type -> %d } ", current->type);
//         current = current->next;
//     }
//     printf("\n");

//    // printLinkedList(tokens);

//     // Free memory if needed
//     free_list(tokens);
// }
//     return (0);
// }
// void ll()
// {
//     system("leaks -q a.out");
// }

int	main(void)
{
	// atexit(ll);
	while (1)
	{
		char *input = readline("minishell$");

		t_token *tokens = convert_to_node(input);
		if (!tokens)
		{
			free(tokens);
			return (0);
		}
		if (check_error(&tokens) == 1)
		{
			// printf("minishell : syntax error"); /*free*/
			free_list(tokens);
			return (0);
		}
		t_cmd *cmd = list_cmd(tokens);
		print_cmd(cmd);

		// t_cmd *newlst = cmd;
		// printf("%s\n",newlst->arg[0]);
		// printf("%s\n",newlst->infile[0]);

		// newlst = newlst->next;
		// printf("%s\n",newlst->arg[0]);
		// printf("%s\n",newlst->infile[0]);
		// printcmdLinkedList(cmd);

		// printf("%s\n",cmd->infile[0]);
		// int count = count_args(tokens);
		// int nb = count_outfiles(tokens);
		// int n = count_infiles(tokens);
		// printf("the number of infiles is %d \n", n);
		// printf("the number of outfiles is %d \n", nb);
		//  printf("the number of args is %d\n", count);
		// char **cmd = get_args(tokens);
		// int i = 0;
		// while (count  >= 0)
		// {
		//      printf("cmd[%d] = %s\n",i,cmd[i]);
		//     //printf("%s\n", cmd[i]);
		//     count--;
		//     i++;
		// }
		// char **infiles = get_infiles(tokens);
		// int j = 0;
		// while (n >= 0)
		// {
		//     printf("infiles[%d] = %s\n",j,infiles[j]);
		//     n--;
		//     j++;
		// }
		// char **outfiles = get_outfiles(tokens);
		// int k = 0;
		// while (nb >= 0)
		// {
		//     printf("outfiles[%d] = %s\n",k,outfiles[k]);
		//     nb--;
		//     k++;
		// }

		// int cnt = count_append_files(tokens);
		// char **append_files = get_append_files(tokens);
		// int a = 0;
		// while (cnt >= 0)
		// {
		//     printf("append_files[%d] = %s\n",a,append_files[a]);
		//     cnt--;
		//     a++;
		// }
		// int tmp = count_herdoc_files(tokens);
		// char **herdoc_files = get_herdoc_files(tokens);
		// int h= 0;
		// while (tmp >= 0)
		// {
		//     printf("herdocfiles[%d] = %s\n",h,herdoc_files[h]);
		//     tmp--;
		//     h++;
		// }

		if (!tokens)
		{
			free(tokens);
			return (0);
		}
		if (check_error(&tokens) == 1)
		{
			// printf("minishell : syntax error"); /*free*/
			free_list(tokens);
			exit(1);
			return (0);
		}
		// t_cmd *cmd = convert_to_cmd(&tokens)
		//------------
		t_token *current = tokens;

		while (current)
		{
			printf("{token -> %s } ", current->token);
			printf("{type -> %d } ", current->type);
			current = current->next;
		}
		printf("\n");

		printlinkedlist(tokens);

		// Free memory if needed
		free_list(tokens);
	}
	return (0);
}