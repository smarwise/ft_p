/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarwise <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 07:45:32 by smarwise          #+#    #+#             */
/*   Updated: 2019/11/26 07:45:34 by smarwise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

void    read_to_file(char *args[2])
{
    int fd;
    pid_t pid;

    pid = fork();
    if ( pid == 0)
    {
        fd = open("temp.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
        dup2(fd, 1);
        execv("/bin/ls", args);
        close(fd);
        exit(0);
    }
    else
        wait4(pid, 0, 0, 0);
}

void    get_file_len(int *ressize, char **result, char **buf)
{
    int fd;
    char buffer[1001];
    int numbytes;

    ft_memset(buffer, '\0', 1001);
    fd = open("temp.txt", O_RDONLY);
    *ressize = 0;
    while ((numbytes = read(fd, buffer, 1000)) > 0)
    {
        *ressize += numbytes;
    }
    close(fd);
    *result = malloc(sizeof(char) * (*ressize + 5));
    *buf = malloc(sizeof(char) * (*ressize + 5));
    ft_memset(*result, '\0', *ressize + 5);
    ft_memset(*buf, '\0', *ressize + 5);
    *result[0] = ' ';
}

void    reader(char **result, int *ressize, char **buf, char *args[2])
{
    int k;
    int fd;

    k = 0;
    read_to_file(args);
    get_file_len(ressize, result, buf);
    fd = open("temp.txt", O_RDONLY);
    while (read(fd, *buf, 2000) > 0)
    {
        if (k != 0)
        {
            *ressize += *ressize;
            *result = realloc(*result, *ressize);
        }
        *result = ft_strcat(*result, *buf);
        ft_memset(*buf, '\0', *ressize + 5);
        k++;
    }
    close(fd);
    unlink("temp.txt");
}

int     sendall(int fd, char *buf, int len, char *client_number)
{
    int total;
    int bytesleft;
    int n;
    char *size;
    char *new;

    total = 0;
    size = ft_itoa(len);
    new = ft_strjoin(size, buf);
    len = ft_strlen(new);
    bytesleft = len;
    while (total < len)
    {
        n = send(fd, new+total, bytesleft, 0);
        if (n == -1)
            handle_error(6);
        total += n;
        bytesleft -= n;
    }
    print_msg("\033[1;32mls was a SUCCESS\033[0m", client_number);
    return (total);
}

void	ls_dir(int fd, char *client_number, char *str)
{
    char *result;
    int ressize;
    char *buf;
    char **array;
    int bytessent;

    print_cmd("ls", client_number);
    array = ft_strsplit(str, ' ');
    if (arraylen(array) == 2)
    {
        char *args[3] = {"ls", array[1], NULL};
        reader(&result, &ressize, &buf, args);
    }
    else
    {
        char *args[2] = {"ls", NULL};
        reader(&result, &ressize, &buf, args);
    }
    bytessent = sendall(fd, result, ft_strlen(result), client_number);
    if (bytessent == 0)
        handle_error(7);
}
