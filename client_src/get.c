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

int				check_file_exists(char *filename, char *name)
{
	char		*old_name;
	struct stat	st;
	int			fd;
	int			n;
	
	old_name = ft_strjoin("files/", name);
	fd = open(old_name, O_RDONLY);
	n = 1;
	if (fstat(fd, &st) < 0)
	{
		ft_err("No such file in server");
		n = -1;
	}
	close(fd);
	if ((fd = open(filename, O_RDONLY)) != -1)
	{
		put_msg(0);
		n = -1;
	}
	close(fd);
	return (n);
}

int				check_valid(char *new_file, int *fd1, char *str)
{
	create_if_not_exists("downloads");
	if (check_file_exists(new_file, str) == -1)
		return (0);
	if ((*fd1 = open(new_file, O_RDWR | O_CREAT,\
					S_IRUSR | S_IWUSR)) == -1)
	{
		put_msg(1);
		return (0);
	}
	return (1);
}

void			handle_get(int fd, char *str)
{
	char		**name;
	int			numbytes;
	char		buf[1000];
	char		*new_file;
	int			fd1;

	name = ft_strsplit(str, ' ');
	new_file = ft_strjoin("downloads/", name[1]);
	ft_memset(buf, '\0', 1000);
	if (check_valid(new_file, &fd1, name[1]))
	{
		if ((send(fd, str, ft_strlen(str), 0)) == -1)
			handle_error(6);
		while ((numbytes = recv(fd, buf, 999, 0)) != -1)
		{
			write(fd1, buf, numbytes);
			if (numbytes < 999)
				break;
		}
		if (numbytes != -1)
			ft_putendl("\033[0;32mDownloading file successful\033[0m");
	}
	free_2d_array((void**)name);
	close(fd1);
}
