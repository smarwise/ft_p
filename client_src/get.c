#include "../includes/client.h"

void    put_msg(int n)
{
    if (n == 0)
        ft_putendl("\033[0;31mFile with same name already exists in client\033[0m");
    if (n == 1)
        ft_putendl("\033[0;31mOpening of new file failed\033[0m");
    return;
}

void    handle_get(int fd, char *str)
{
    char **name;
    int fd1;
    int numbytes;
    char buf[1000];
    char    *new_file;

    name = ft_strsplit(str, ' ');
    new_file = ft_strjoin("downloads/", name[1]);
    if ((fd1 = open(new_file, O_RDONLY)) != -1)
        return (put_msg(0));
    close(fd1);
    if ((fd1 = open(new_file, O_RDWR | O_CREAT,
        S_IRUSR | S_IWUSR)) == -1)
        return(put_msg(1));
    ft_memset(buf, '\0', 1000);
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
    free_2d_array((void**)name);
    close(fd1);
}