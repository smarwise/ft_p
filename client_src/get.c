/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarwise <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 07:42:03 by smarwise          #+#    #+#             */
/*   Updated: 2019/11/26 07:42:05 by smarwise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/client.h"

void    create_if_not_exists(char *dir_name)
{
    struct stat st;

    if (stat(dir_name, &st) == -1)
        mkdir(dir_name, 0700);
}

int   put_msg(int n)
{
	if (n == 0)
		ft_putendl("\033[0;31mFile with same name already exists in client\033[0m");
	if (n == 1)
		ft_putendl("\033[0;31mOpening of new file failed\033[0m");
	return (-1);
}

int				check_file_exists(char *filename)
{
	int			fd;
	
	if ((fd = open(filename, O_RDONLY)) != -1)
	{
		put_msg(0);
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int				check_valid(char *new_file, int *fd1)
{
	create_if_not_exists("downloads");
	if (check_file_exists(new_file) == -1)
		return (0);
	if ((*fd1 = open(new_file, O_RDWR | O_CREAT,\
					S_IRUSR | S_IWUSR)) == -1)
	{
		put_msg(1);
		return (0);
	}
	return (1);
}

void			create_file_if_not_err(int fd, char buf[1000], int fd1)
{
	int numbytes;
	int k;

	k = 0;
	while ((numbytes = recv(fd, buf, 999, 0)) != -1)
	{
		if (k == 0)
		{
			if (ft_strcmp("Get error: ", ft_strsub(buf, 0, 11)) == 0)
			{
				ft_putendl(buf);
				return ;
			}
		}
		write(fd1, buf, numbytes);
		if (numbytes < 999)
			break;
		k++;
	}
	if (numbytes != -1)
		ft_putendl("\033[0;32mDownloading file successful\033[0m");
}

void			handle_get(int fd, char *str)
{
	char		**name;
	char		buf[1000];
	char		*new_file;
	int			fd1;

	name = ft_strsplit(str, ' ');
	new_file = ft_strjoin("downloads/", name[1]);
	ft_memset(buf, '\0', 1000);
	if (check_valid(new_file, &fd1))
	{
		if ((send(fd, str, ft_strlen(str), 0)) == -1)
			handle_error(6);
		create_file_if_not_err(fd, buf, fd1);
	}
	free_2d_array((void**)name);
	close(fd1);
}
