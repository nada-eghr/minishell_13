/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naessgui <naessgui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:53:48 by naessgui          #+#    #+#             */
/*   Updated: 2025/06/20 21:35:32 by naessgui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include"minishell.h"

 static int	count(long nb)
{
	int	count;

	count = 0;
	if (nb < 0)
	{
		count += 1;
		nb = -nb;
	}
	if (nb == 0)
		count = 1;
	while (nb > 0)
	{
		nb /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	nbr;
	int		c;

	nbr = n;
	c = count(n);
	str = malloc(c + 1);
	if (!str)
		return (NULL);
	str[c] = '\0';
	if (nbr < 0)
		nbr = -nbr;
	c -= 1;
	while (c >= 0)
	{
		str[c] = nbr % 10 + '0';
		nbr /= 10;
		c--;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
char *get_value(char *str, t_env_list *env)
{
    t_env_list *tmp ;
    // int i = 0;
    tmp = env;
    // char *status ;
    
    str++;
    while (tmp->next)
    {
        // if(str[i] == '$' || str[i] == '?')
        //     status = ft_itoa(exit_sta);
        //  printf("key = %s \n", tmp->content.key);
        //  printf("token = %s \n", str);
        if (ft_strcmp(str,tmp->content.key) == 0){
            // printf("value = %s \n", tmp->content.value);
            return(tmp->content.value);
        }
        tmp = tmp->next;
    }
    return NULL;
    
}
t_token *expand_token(t_token *token , t_env_list *env)
{
    t_token *tmp;
    tmp = token;
    char *new_data;
    // int i = 0;
    int j = 0;
    char *s1;
    char *s2;
    t_token *prev;
    
    prev = tmp;
    prev->type = -1;
    
    // int i = 0;
    // while(env->next){
	// 	printf("key %s ->",env->content.key);
	// 	printf("value = %s \n", env->content.value);
	// 	env = env->next;
	// }
    while ( tmp )
    {
        if (tmp->type == TOKEN_ENV_VAR && prev->type != TOKEN_HERDOC)
        {
            new_data = get_value(tmp->token , env);
            free(tmp->token);
            if (new_data)
                tmp->token = ft_strdup(new_data);
            else
                tmp->token = ft_strdup("");
        }
        else if (tmp->type == TOKEN_D_QUOTE && prev->type != TOKEN_HERDOC)
        {
            new_data = tmp->token;
            while(new_data[j] != '$' && new_data[j])
                j++;
            s1 = substr(new_data, 1, j -1);
            s2 = substr(new_data, j , ft_strlen(new_data) - j - 1);
            new_data = ft_strjoin(s1, get_value(s2, env));
            free(tmp->token);
            if (new_data)
                tmp->token = ft_strdup(new_data);
            else
                tmp->token = ft_strdup("");
        }
        else if (tmp->type == TOKEN_WORD && ft_strchr(tmp->token , '$') && prev->type != TOKEN_HERDOC)
        {
            new_data = tmp->token;
            while(new_data[j] != '$' && new_data[j])
                j++;
            s1 = substr(new_data, 0, j);
            s2 = substr(new_data, j , ft_strlen(new_data) - j);
            new_data = ft_strjoin(s1, get_value(s2, env));
            printf("new_data = %s\n",new_data);
            printf("s1 = %s\n", s1);
            printf("s2 = %s\n", s2);
            free(tmp->token);
            if (new_data)
                tmp->token = ft_strdup(new_data);
            else
                tmp->token = ft_strdup("");
            printf("token = %s\n",tmp->token);
        }
      
        prev = tmp;
        tmp = tmp->next;
        
    }
    return (token);
}