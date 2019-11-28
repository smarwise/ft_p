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

void	show_pwd(t_var *var)
{
	char *path;

    print_cmd("pwd", var->client_number);
	path = (char *)malloc(sizeof(char) * FILENAME_MAX);
	if ((getcwd(path, FILENAME_MAX)) == NULL)
    {
        print_msg("\033[1;31mpwd was a FAILURE\033[0m", var->client_number);
        if ((send(var->fd, "fail", 4, 0)) == -1)
            print_msg("\033[1;32mfailed to send fail message\033[0m", var->client_number);
        exit(0);
    }
	if ((send(var->fd, path, ft_strlen(path), 0)) != -1)
        print_msg("\033[1;32mpwd was a SUCCESS\033[0m", var->client_number);
    else
        print_msg("\033[1;31mpwd was a FAILURE\033[0m", var->client_number);
}

void    cd_dir(t_var *var, char *str)
{
    char **cmd;

    print_cmd(str, var->client_number);
    cmd = ft_strsplit(str, ' ');
    if (chdir(cmd[1]) == 0)
    {
        print_msg("\033[0;33mDirectory change success\033[0m", var->client_number);
        if (send(var->fd, "success", 7, 0) == -1)
            handle_error(6);
    }
    else
    {
        print_msg("\033[0;31mDirectory change failed\033[0m", var->client_number);
        if (send(var->fd, "fail", 4, 0) == -1)
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
        send(fd1, "31 Get error: File does not exist", 34, 0);
        close(fd);
        return (-1);
    }
    if (S_ISDIR(st.st_mode))
    {
        send(fd1, "40 Get error: Selected file is a directory", 43, 0);
        close(fd);
        return (-1);
    }
    if (fd == -1)
    {
        send(fd1, "45 Get error: Selected file cannot be processed", 48, 0);
        close(fd);
        return (-1);
    }
    close(fd);
    return (1);
}

int     get_file_size(int fd)
{
    int total;
    int numbytes;
    char buf[1000];

    total = 0;
    numbytes = 0;
    while ((numbytes = read(fd, buf, 1000)) > 0)
    {
       total += numbytes;
    }
    return (total);
}

int    create_file(int *fd1, char *path, char *str, int fd, int *size)
{
    char *name;
    char *temp;
    char **arr;

    arr = ft_strsplit(str, ' ');
    temp = ft_strjoin(path, "/");
    name = ft_strjoin(temp, arr[1]);
    if ((check_if_file(name, fd)) == -1)
        return (-1);
    if ((*fd1 = open(name, O_RDONLY)) == -1)
    {
        send(fd, "\033[1;31mFail: no such file exits in server\033[0m", 46, 0);
        return (-1);
    }
    *size = get_file_size(*fd1);
    close(*fd1);
    *fd1 = open(name, O_RDONLY);
    return (1);
}

void    get_file(t_var *var, char *str)
{
    int fd1;
    char buf[1000];
    int numbytes;
    char *path;
    int k;
    int size;
    char *temp;
    char *temp2;

    k = 0;
    print_cmd(str, var->client_number);
    path = (char *)malloc(sizeof(char) * FILENAME_MAX);
	if ((getcwd(path, FILENAME_MAX)) == NULL)
    {
        print_msg("\033[1;31m\033[0m", var->client_number);
        send_result(-1, var->fd);
    }
    if ((create_file(&fd1, path, str, var->fd, &size)) == -1)
        return ;
    ft_memset(buf, '\0', 1000);
    while ((numbytes = read(fd1, buf, 999)) > 0)
    {
        if (k == 0)
        {
            temp = ft_strjoin(ft_itoa(size), " ");
            temp2 = ft_strjoin(temp, buf);
            send(var->fd, temp2, ft_strlen(temp) + numbytes, 0);
        }
        else
        {
            if ((send(var->fd, buf, numbytes, 0)) == -1)
            {
                print_msg("\033[1;31mFail: no such file exits in server\033[0m", var->client_number);
                send_result(-1, var->fd);
            }
        }
        ft_memset(buf, '\0', 1000);
        k++;
    }
    print_msg("\033[1;32mGet file successful\033[0m", var->client_number);
    close(fd1);
}
