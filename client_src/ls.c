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


char 		*receive_all(int fd, int numbytes, int total)
{
	char	*buf;
	char 	tmp[1000];

	buf = NULL;
	ft_memset(tmp, '\0', 1000);
	buf = (char *)malloc(sizeof(char) * (1000));
	ft_memset(buf, '\0', 1000);
	total = 0;
	ft_memset(tmp, '\0', 1000);
	while ((numbytes = recv(fd, tmp, 999, 0)) > 0)
	{
	    buf = ft_strcat(buf, tmp);
	    total += numbytes;
	    if (numbytes < 999)
	    	break;
	    buf = realloc(buf, total + 1000);
		ft_memset(tmp, '\0', 1000);
	}
	buf[total + 1] = '\0';
	return(buf);
}

int			check_input(char *str)
{
	char **array;
	
	array = ft_strsplit(str, ' ');
	if (arraylen(array) <= 2)
		return (1);
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
		contents = receive_all(fd, 0, 0);
		print_arr(ft_strsplit(contents, '\n'));
		free(contents);
	}
	else
		ft_err("Error in command or flags");
}
