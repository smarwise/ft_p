/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarwise <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 07:45:51 by smarwise          #+#    #+#             */
/*   Updated: 2019/11/26 07:45:54 by smarwise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

void    create_if_not_exists(char *dir_name)
{
    struct stat st;

    if (stat(dir_name, &st) == -1)
        mkdir(dir_name, 0700);
}

char    *get_file_name(char *str, char *files)
{
    char **name;
    char *file_name;
    char **namme;
    int i;
    int len;

    i = 0;
    name = ft_strsplit(str, ' ');
    namme = ft_strsplit(name[1], '/');
    while (namme[i] != NULL)
        i++;
    len = ft_strlen(namme[i - 1]);
    file_name = (char *)malloc(sizeof(char) * (ft_strlen(files)));
    ft_memset(file_name, '\0', (len + 7));
    file_name = ft_strcpy(file_name, files);
    file_name = ft_strcat(file_name, namme[i - 1]);
    return (file_name);
}

int     check_file(char *file_name, int fd, char *client_number)
{
    int fd1;

    fd1 = open(file_name, O_RDONLY);
    if (fd1 != -1)
    {
        print_msg("\033[1;31mFail: file already exists in server\033[0m", client_number);
        send_result(-1, fd);
        close(fd1);
        return -1;
    }
    close(fd1);
    return 0;
}

int    make_file(int fd, int fd1, char *file_name)
{
    char buf[1000];
    int numbytes;

    ft_putendl(file_name);
    if ((fd1 = open(file_name, O_RDWR | O_CREAT,
        S_IRUSR | S_IWUSR)) == -1)
    {
        send_result(-1, fd);
        handle_error(8);
    }
    if ((send(fd, "ready", 5, 0)) == -1)
            handle_error(6);
    while ((numbytes = recv(fd, buf, 999, 0)) != -1)
    {
        write(fd1, buf, numbytes);
        if (numbytes < 999)
            break;
    }
    if (numbytes == -1)
    {
        send_result(-1, fd);
        return -1;
    }
    return (0);
}

void    put_file(int fd, char *str, char *client_number, char *owd)
{
    char *file_name;
    int fd1;
    char *f;
    char *files;

    print_cmd(str, client_number);
    fd1 = 0;
    f = ft_strjoin(owd, "/");
    files = ft_strjoin(f, "files/");
    file_name = get_file_name(str, files);
    if (check_file(file_name, fd, client_number) == -1)
        return;
    create_if_not_exists(files);
    if (make_file(fd, fd1, file_name) == -1)
        return;
    else
    {
        send_result(1, fd);
        print_msg("\033[1;32mFile put was a success\033[0m", client_number);
    }
}
