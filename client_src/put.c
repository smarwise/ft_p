#include "../includes/client.h"

void		handle_exit(int fd)
{
	close(fd);
	ft_putendl("\033[0;33mConnection successfully closed\033[0m");
	exit(0);
}

int     check_if_file(char *filename)
{
    struct stat st;
    int fd;
    int n;

    fd = open(filename, O_RDONLY);
    n = 1;
    if (fstat(fd, &st) < 0)
        return -1;
    if (S_ISDIR(st.st_mode))
    {
        ft_err("Selected file is a directory");
        n = -1;
    }
    else if (fd == -1)
    {
        ft_err("Selected file cannot be processed");
        n = -1;
    }
    close(fd);
    return (n);
}

int    get_ready(int fd, char buf[1000], char **file, char *str)
{
    int numbytes;
    
    ft_memset(buf, '\0', 1000);
    if (check_if_file(file[1]) == -1)
        return (-1);
    if ((send(fd, str, ft_strlen(str), 0)) == -1)
        handle_error(6);
    if ((numbytes = recv(fd, buf, 6, 0)) == -1)
    {
        handle_fail_success(-1);
        return -1;
    }
    if (ft_strncmp(buf, "ready", 5) != 0)
    {
        handle_fail_success(-1);
        ft_putendl("File already exists in server");
        return -1;
    }
    return 0;
}

void    handle_put(int fd, char **file, char *str)
{
    int fd2;
    char buf[1000];
    int numbytes;

    if (get_ready(fd, buf, file, str) == -1)
        return;
    fd2 = open(file[1], O_RDONLY);
    while ((numbytes = read(fd2, buf, 1000)) > 0)
    {
        if ((send(fd, buf, numbytes, 0)) == -1)
            handle_error(6);
    }
    if ((numbytes = recv(fd, buf, 19, 0)) == -1)
        handle_fail_success(-1);
    else if (numbytes > 0)
    {
        buf[numbytes] = '\0';
        if (ft_strcmp(buf, "fail") == 0)
            handle_fail_success(-1);
        else
            handle_fail_success(0);
    }
}