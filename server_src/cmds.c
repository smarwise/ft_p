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

void	ls_dir(int fd)
{
	int pid;
    int fd2;
    char *result;
    int ressize;
    int k;
    char *buf;

    k = 0;
    ressize = 2000;
    result = malloc(sizeof(char) * 2000);
    buf = malloc(sizeof(char) * 2000);
    char *args[2] = {"ls", NULL};
    pid = fork();
    if (pid == 0)
    {
        fd2 = open("temp.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
        dup2(fd2, 1);
    	execv("/bin/ls", args);
        close(fd2);
        exit(0);
    }
    fd2 = open("temp.txt", O_RDONLY);
    while (read(fd2, buf, 2000) > 0)
    {
        if (k != 0)
        {
            ressize += ressize;
            result = realloc(result, ressize);
        }
        result = ft_strcat(result, buf);
        k++;
    }
    free(buf);
	if ((send(fd, result, ft_strlen(result), 0)) != -1)
        ft_putendl("\033[1;32mls was a SUCCESS\033[0m");
    else
        ft_putendl("\033[1;31mls was a FAILURE\033[0m");
}