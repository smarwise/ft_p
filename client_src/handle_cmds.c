#include "../includes/client.h"

void		handle_exit(int fd)
{
	close(fd);
	ft_putendl("\033[0;33mConnection successfully closed\033[0m");
	exit(0);
}

void		handle_pwd(int fd)
{
	char *buf;
	int numbytes;
	
	buf = (char *)malloc(sizeof(char) * 100);
	if ((send(fd, "pwd", 3, 0)) == -1)
        handle_error(6);
    if ((numbytes = recv(fd, buf, MAXDATASIZE-1, 0)) == -1)
        handle_fail_success(-1);
    if (numbytes > 0)
    {
    	if (ft_strcmp(buf, "fail") == 0)
    		handle_fail_success(-1);
    	handle_fail_success(0);
        buf[numbytes] = '\0';
        ft_putendl(buf);
        ft_putstr("\033[0m");
    }
    free(buf);
    buf = NULL;
}

void	handle_cd(int fd, char *str)
{
    int numbytes;
    char buf[20];

    numbytes = 0;
    ft_memset(buf, '\0', 20);
	if ((send(fd, str, ft_strlen(str), 0)) == -1)
        handle_error(6);
    if ((numbytes = recv(fd, buf, 19, 0)) == -1)
        handle_fail_success(-1);
    if (numbytes > 0)
    {
        if (ft_strcmp(buf, "fail") == 0)
            handle_fail_success(-1);
        else
            handle_fail_success(0);
    }
}

int    get_ready(int fd, char buf[1000], char **file, char *str)
{
    int numbytes;
    int f_d;
 
    ft_memset(buf, '\0', 1000);
    if ((f_d = open(file[1], O_RDONLY)) == -1)
    {
        handle_error(7);
        return -1;
    }
    if ((send(fd, str, ft_strlen(str), 0)) == -1)
        handle_error(6);
    if ((numbytes = recv(fd, buf, 6, 0)) == -1)
    {
        handle_fail_success(-1);
        return -1;
    }
    ft_putendl(buf);
    ft_putnbr(numbytes);
    // if (numbytes > 0)
    // {
        // buf[numbytes] = '\0';
        if (ft_strncmp(buf, "ready", 5) != 0)
        {
            ft_putendl("not ready");
            handle_fail_success(-1);
            return -1;
        }
        ft_putendl("ready");
    // }
    close(f_d);
    return 0;
}

void    handle_put(int fd, char *str)
{
    char **file;
    int f_d;
    char buf[1000];
    int numbytes;

    file = ft_strsplit(str, ' ');
    f_d = open(file[1], O_RDONLY);
    if (get_ready(fd, buf, file, str) == -1)
        return;
    while ((numbytes = read(f_d, buf, 1000)) > 0)
    {
        if ((send(fd, buf, numbytes, 0)) == -1)
            handle_error(6);
    }
    if ((numbytes = recv(fd, buf, 19, 0)) == -1)
    {
        handle_fail_success(-1);
        return;
    }
    if (numbytes > 0)
    {
        buf[numbytes] = '\0';
        if (ft_strcmp(buf, "fail") == 0)
            handle_fail_success(-1);
        else
            handle_fail_success(0);
    }
    free_2d_array((void**)file);
    file = NULL;
}

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

    name = ft_strsplit(str, ' ');
    if ((fd1 = open(name[1], O_RDONLY)) != -1)
        return (put_msg(0));
    close(fd1);
    if ((fd1 = open(name[1], O_RDWR | O_CREAT,
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