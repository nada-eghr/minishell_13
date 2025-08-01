/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gt_l.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slamhaou <slamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 11:46:00 by slamhaou          #+#    #+#             */
/*   Updated: 2025/07/30 12:01:57 by slamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif

char *str_dupp(char *s)
{
	int	i;
	char *new_str;
	
	if (!s)
		return(NULL);
	i = 0;
	new_str = malloc( 1 * (ft_strlen(s) + 1));
	while (s[i])
	{
		new_str[i] = s[i];
		i++;
	}
	new_str[i] = '\0';
	return(new_str);
}
char	*str_j(char *rem, char *buff)
{
	int	i;
	int j;
	char *new;

	if (!rem && buff)
		return(str_dup(buff));
	if (!buff && rem)
	{
		new = str_dup(rem);
		free(rem);
		return(new);
	}
	if (!buff && !rem)
		return(NULL);
	i = 0;
	j = 0;
	new = malloc(1 * (ft_strlen(rem) + ft_strlen(buff) + 1));
	while (rem[i])
		new[j++] = rem[i++];
	i = 0;
	while (buff[i])
		new[j++] = buff[i++];
	new[j] = '\0';
	free(rem);
	return(new);
}
int	serch(char *romind, int c)
{
	int	i;

	if (!romind)
		return(0);
	i = 0;
	while (romind[i])
	{
		if (romind[i] == c)
			return(1);
		i++;
	}
	return(0);
}

char	*get_new_line(char *romind, int *n)
{
	int	i;
	int	j;
	char *new;

	i = 0;
	j = 0;
	while (romind[i] != '\n')
		i++;
	if (romind[i] == '\n')
		i++;
	new = malloc(1 * (i + 1));
	while (j < i)
	{
		new[j] = romind[j];
		j++;
	}
	new[j] = '\0';
	*n = i;
	return(new);
}
char	*new_rom(char *romind, int i)
{
	char	*new_rom;
	int j;

	j = 0;
	if (romind[i] == '\0')
		return(free(romind), NULL);
	new_rom = malloc( 1 * (ft_strlen(&romind[i]) + 1));
	while (romind[i])
		new_rom[j++] = romind[i++];
	new_rom[j] = '\0';
	free(romind);
	return(new_rom);
}
char	*get_linee(int fd, char *buffer)
{
	long	red;
	static char *romind;
	char *line;
	int	i;

	i = 0;
	while (serch(romind, '\n') == 0)
	{
		red = read(fd, buffer, BUFFER_SIZE);
		if (red < 0 || errno == EINTR)
			return(NULL);
		if (red == 0 && !romind)
			return (NULL);
		if (red == 0 && romind)
		{
			line = str_dupp(romind);
			free(romind);
			romind = NULL;
			return(line);
		}
		buffer[red] = '\0';
		romind = str_j(romind, buffer);
	}
	line = get_new_line(romind, &i);
	romind = new_rom(romind, i);
	return(line);
}
char *get_next_line(int fd)
{
	char *buff;
	char *line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return(NULL);
	buff = malloc(BUFFER_SIZE + 1);
	line = get_linee(fd, buff);
	free(buff);
	return(line);
}