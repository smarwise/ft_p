#include "../includes/server.h"

void    reader(char **result, int *ressize, char **buf, char *args[2])
{
    int k;
    int fd;

    k = 0;
    if (!fork())
    {
        fd = open("temp.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
        dup2(fd, 1);
        execv("/bin/ls", args);
        close(fd);
        exit(0);
    }
    fd = open("temp.txt", O_RDONLY);
    while (read(fd, *buf, 2000) > 0)
    {
        if (k != 0)
        {
            *ressize += *ressize;
            *result = realloc(*result, *ressize);
        }
        *result = ft_strcat(*result, *buf);
        k++;
    }
    close(fd);
}

int     sendall(int fd, char *buf, int len)
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
    ft_putendl("\033[1;32mls was a SUCCESS\033[0m");
    free(size);
    free(new);
    return (total);
}

void	ls_dir(int fd)
{
    char *result;
    int ressize;
    char *buf;
    int len;
    int bytessent;

    ressize = 2000;
    result = malloc(sizeof(char) * 2000);
    buf = malloc(sizeof(char) * 2000);
    ft_memset(result, '\0', 2000);
    ft_memset(buf, '\0', 2000);
    result[0] = ' ';
    char *args[2] = {"ls", NULL};
    reader(&result, &ressize, &buf, args);
    ft_putendl(result);
    len = ft_strlen(result);
    free(buf);
    bytessent = sendall(fd, result, len);
    if (bytessent == 0)
        handle_error(7);
    free(result);
}