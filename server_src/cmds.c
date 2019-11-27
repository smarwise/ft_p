/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarwise <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 07:45:07 by smarwise          #+#    #+#             */
/*   Updated: 2019/11/26 07:45:08 by smarwise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

void	show_pwd(int fd, char *client_number)
{
	char *path;

    print_cmd("pwd", client_number);
	path = (char *)malloc(sizeof(char) * FILENAME_MAX);
	if ((getcwd(path, FILENAME_MAX)) == NULL)
    {
        print_msg("\033[1;31mpwd was a FAILURE\033[0m", client_number);
        if ((send(fd, "fail", 4, 0)) == -1)
            print_msg("\033[1;32mfailed to send fail message\033[0m", client_number);
        exit(0);
    }
	if ((send(fd, path, ft_strlen(path), 0)) != -1)
        print_msg("\033[1;32mpwd was a SUCCESS\033[0m", client_number);
    else
        print_msg("\033[1;31mpwd was a FAILURE\033[0m", client_number);
}

void    cd_dir(int fd, char *str, char *client_number)
{
    char **cmd;

    print_cmd(str, client_number);
    cmd = ft_strsplit(str, ' ');
    if (chdir(cmd[1]) == 0)
    {
        print_msg("\033[0;33mDirectory change success\033[0m", client_number);
        if (send(fd, "success", 7, 0) == -1)
            handle_error(6);
    }
    else
    {
        print_msg("\033[0;31mDirectory change failed\033[0m", client_number);
        if (send(fd, "fail", 4, 0) == -1)
            handle_error(6);
    }
}

int     check_if_file(char *filename, int fd1)
{
    struct stat st;
    int fd;

    fd = open(filename, O_RDONLY);
    if (fstat(fd, &st) < 0)
    {
        send(fd1, "Get error: File does not exist", 31, 0);
        return (-1);
    }
    if (S_ISDIR(st.st_mode))
    {
        send(fd1, "Get error: Selected file is a directory", 40, 0);
        return (-1);
    }
    if (fd == -1)
    {
        send(fd1, "Get error: Selected file cannot be processed", 45, 0);
        return (-1);
    }
    close(fd);
    return (1);
}


int    create_file(int *fd1, char *path, char *str, int fd)
{
    char *name;
    char *temp;
    char **arr;
    int n;

    n = 1;
    arr = ft_strsplit(str, ' ');
    temp = ft_strjoin(path, "/");
    name = ft_strjoin(temp, arr[1]);
    ft_putendl(name);
    if ((check_if_file(name, fd)) == -1)
        return (-1);
    if ((*fd1 = open(name, O_RDONLY)) == -1)
    {
        send(fd, "\033[1;31mFail: no such file exits in server\033[0m", 46, 0);
        return (-1);
    }
    return (1);
}

void    get_file(int fd, char *str, char *client_number)
{
    int fd1;
    char buf[1000];
    int numbytes;
    char *path;

    print_cmd(str, client_number);
    path = (char *)malloc(sizeof(char) * FILENAME_MAX);
	if ((getcwd(path, FILENAME_MAX)) == NULL)
    {
        print_msg("\033[1;31m\033[0m", client_number);
        send_result(-1, fd);
    }
    if (!(create_file(&fd1, path, str, fd)))
        return ;
    while ((numbytes = read(fd1, buf, 1000)) > 0)
    {
        if ((send(fd, buf, numbytes, 0)) == -1)
        {
            print_msg("\033[1;31mFail: no such file exits in server\033[0m", client_number);
            send_result(-1, fd);
        }
    }
    print_msg("\033[1;32mGet file successful\033[0m", client_number);
    close(fd1);
}
