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

void    reader(char **result, int *ressize, char **buf, char *args[2])
{
    int k;
    int fd;

    k = 0;
    read_to_file(args);
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
    // free(size);
    // free(new);
    return (total);
}

void	ls_dir(int fd, char *client_number)
{
    char *result;
    int ressize;
    char *buf;
    int len;
    int bytessent;

    print_cmd("ls", client_number);
    ressize = 2000;
    result = malloc(sizeof(char) * 2000);
    buf = malloc(sizeof(char) * 2000);
    ft_memset(result, '\0', 2000);
    ft_memset(buf, '\0', 2000);
    result[0] = ' ';
    char *args[2] = {"ls", NULL};
    reader(&result, &ressize, &buf, args);
    len = ft_strlen(result);
    bytessent = sendall(fd, result, len, client_number);
    if (bytessent == 0)
        handle_error(7);
}