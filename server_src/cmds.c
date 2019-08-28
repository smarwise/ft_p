#include "../includes/server.h"

void	show_pwd(int fd)
{
	char *path;

	path = (char *)malloc(sizeof(char) * FILENAME_MAX);
	if ((getcwd(path, FILENAME_MAX)) == NULL)
    {
        ft_putendl("\033[1;31mpwd was a FAILURE\033[0m");
        if ((send(fd, "fail", 4, 0)) == -1)
            ft_putendl("\033[1;32mfailed to send fail message\033[0m");
        exit(0);
    }
	if ((send(fd, path, ft_strlen(path), 0)) != -1)
        ft_putendl("\033[1;32mpwd was a SUCCESS\033[0m");
    else
        ft_putendl("\033[1;31mpwd was a FAILURE\033[0m");
    free(path);
}

void    cd_dir(int fd, char *str)
{
    char **cmd;

    cmd = ft_strsplit(str, ' ');
    if (chdir(cmd[1]) == 0)
    {
        ft_putendl("\033[0;33mDirectory change success\033[0m");
        if (send(fd, "success", 4, 0) == -1)
            handle_error(6);
    }
    else
    {
        ft_putendl("\033[0;31mDirectory change failed\033[0m");
        if (send(fd, "fail", 4, 0) == -1)
            handle_error(6);
    }
    (void)fd;
}

char    *get_file_name(char *str)
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
    file_name = (char *)malloc(sizeof(char) * (len + 7));
    file_name = ft_strcpy(file_name, "files/");
    file_name = ft_strcat(file_name, namme[i - 1]);
    free_2d_array((void**)namme);
    free_2d_array((void**)name);
    return (file_name);
}

int     check_file(char *file_name, int fd)
{
    char buf[1000];
    int numbytes;

    if (open(file_name, O_RDONLY) != -1)
    {
        ft_putendl("\033[1;31mFail: file already exists in server\033[0m");
        send_result(-1, fd);
        while ((numbytes = recv(fd, buf, 999, 0)) != -1)
        {
            if (numbytes < 999)
                break;
        }
        return -1;
    }
    return 0;
}

int    make_file(int fd, int fd1, char *file_name)
{
    char buf[1000];
    int numbytes;

    if ((fd1 = open(file_name, O_RDWR | O_CREAT,
        S_IRUSR | S_IWUSR)) == -1)
    {
        send_result(-1, fd);
        handle_error(8);
    }
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

void    put_file(int fd, char *str)
{
    char *file_name;
    int fd1;

    file_name = get_file_name(str);
    fd1 = 0;
    if (check_file(file_name, fd) == -1)
        return;
    if (make_file(fd, fd1, file_name) == -1)
        return;
    else
    {
        send_result(1, fd);
        ft_putendl("\033[1;32mFile put was a success\033[0m");
    }
    free(file_name);
}

void    get_file(int fd, char *str)
{
    ft_putendl(str);
    (void)fd;
}
