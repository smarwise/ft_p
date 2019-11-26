/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarwise <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 07:42:28 by smarwise          #+#    #+#             */
/*   Updated: 2019/11/26 07:42:30 by smarwise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/client.h"

void	print_arr(char **ls)
{
	int n;

	n = 0;
	while (ls[n])
    {
        if (!(ft_strstr(ls[n], "temp.txt")))
        {
        	ft_putstr(ls[n]);
        	ft_putstr("\n");
        }
        n++;
    }
	free_2d_array((void**)ls);
    ft_putstr("\n\033[0m");
}

void	get_arr(char *ls, char **arr)
{
	int n;
	int i;
	int j;

	n = 0;
	j = 0;
	while (ls[n])
    {
		i = 0;
		arr[j] = (char*)malloc(sizeof(char) * 3000);
		while (ls[n] != '\n' && ls[n] != '\0')
		{
			arr[j][i] = ls[n];
			n++;
			i++;
		}
		arr[j][i] = '\0';
		j++;
		if (ls[n] == '\n')
			n++;
    }
	arr[j] = NULL;
}

void show_output(char *contents)
{
	char *real_contents;
	int n;
	char **ls;

	n = 0;
	handle_fail_success(0);
	while (contents[n] != ' ')
		n++;
	while (contents[n] == ' ')
		n++;
	real_contents = ft_strsub(contents, n, ft_strlen(contents) - n);
	ls = (char**)malloc(sizeof(char*) * 1000);
	get_arr(real_contents, ls);
	print_arr(ls);
}

char 		*receive_all(int fd)
{
	int buflen;
	char *buf;
	char tmp[1000];
	int numbytes;
	int total;

	numbytes = 0;
	total = 0;
	buf = NULL;
	ft_memset(tmp, '\0', 1000);
	if ((numbytes = recv(fd, tmp, 999, 0)) == -1)
		handle_fail_success(-1);
	buflen = ft_atoi(tmp);
	buf = (char *)malloc(sizeof(char) * (buflen + 2));
	ft_memset(buf, '\0', buflen + 2);
	total += numbytes;
	buf = ft_strcat(buf, tmp);
	while (total < buflen)
	{
		ft_memset(tmp, '\0', 1000);
		if ((numbytes = recv(fd, tmp, 999, 0)) == -1)
			handle_fail_success(-1);
	    buf = ft_strcat(buf, tmp);
	    total += numbytes;
	}
	buf[total + 1] = '\0';
	return(buf);
}

int			check_input(char *str)
{
	char **array;
	char *arr[] = {"-a", "-d", "-F", "-l", "-a", "-lh", "-ls",\
	"-r", "-R", "-S", "-s", "-t", "-x", "-la", "-f", NULL};
	int n;
	
	array = ft_strsplit(str, ' ');
	n = 0;
	if (arraylen(array) <= 2)
	{
		if (arraylen(array) == 2)
		{
			while (arr[n])
			{
				if (ft_strcmp(arr[n], array[1]) == 0)
					return (1);
				n++;
			}
		}
		else
			return (1);
	}
	return (0);
}

void		handle_ls(int fd, char *str)
{
	char *contents;

    contents = NULL;
	if (check_input(str))
	{
		if ((send(fd, str, ft_strlen(str), 0)) == -1)
			handle_error(6);
		contents = receive_all(fd);
		show_output(contents);
		free(contents);
	}
	else
		ft_err("Error in command or flags");
}
