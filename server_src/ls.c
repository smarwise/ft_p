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

void    reader(char **result, int *ressize, char buf[2000], char *args[2])
{
    int k;
    int fd;

    k = 0;
    read_to_file(args);
    ft_memset(buf, '\0', 2000);
    fd = open("temp.txt", O_RDONLY);
    *result = (char *)malloc(sizeof(char) * 2000);
    *ressize = 2000;
    while (read(fd, buf, 1999) > 0)
    {
        if (k != 0)
        {
            *ressize += 2000;
            *result = realloc(*result, *ressize);
        }
        *result = ft_strcat(*result, buf);
        ft_memset(buf, '\0', 2000);
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

    total = 0;
    len = ft_strlen(buf);
    bytesleft = len;
    while (total < len)
    {
        n = send(fd, buf+total, bytesleft, 0);
        if (n == -1)
            handle_error(6);
        total += n;
        bytesleft -= n;
    }
    print_msg("\033[1;32mls was a SUCCESS\033[0m", client_number);
    return (total);
}

void	ls_dir(t_var *var, char *str)
{
    char *result;
    int ressize;
    char buf[2000];
    char **array;
    int bytessent;

    print_cmd("ls", var->client_number);
    array = ft_strsplit(str, ' ');
    if (arraylen(array) == 2)
    {
        char *args[3] = {"ls", array[1], NULL};
        reader(&result, &ressize, buf, args);
    }
    else
    {
        char *args[2] = {"ls", NULL};
        reader(&result, &ressize, buf, args);
    }
    bytessent = sendall(var->fd, result, ft_strlen(result), var->client_number);
    if (bytessent == 0)
        send(var->fd, "\033[0;31mls failed\033[0m", 26, 0);
}
