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
}

void	handle_cd(int fd, char *str)
{
    int numbytes;
    char buf[20];

    numbytes = 0;
	if ((send(fd, str, ft_strlen(str), 0)) == -1)
        handle_error(6);
    if ((numbytes = recv(fd, buf, 19, 0)) == -1)
        handle_fail_success(-1);
    if (numbytes > 0)
    {
        buf[numbytes] = '\0';
        if (ft_strcmp(buf, "fail") == 0)
            handle_fail_success(-1);
        else
            handle_fail_success(0);
    }
}

void    handle_put(int fd, char *str)
{
    char **file;
    int f_d;
    int i;
    char buf[1000];
    int numbytes;

    file = ft_strsplit(str, ' ');
    if ((f_d = open(file[1], O_RDONLY)) == -1)
    {
        handle_error(7);
        return;
    }
    if ((send(fd, str, ft_strlen(str), 0)) == -1)
        handle_error(6);
    while (i <10000)
        i++;
    while ((numbytes = read(f_d, buf, 1000)) > 0)
    {
        if ((send(fd, buf, numbytes, 0)) == -1)
            handle_error(6);
    }
    if ((numbytes = recv(fd, buf, 19, 0)) == -1)
        handle_fail_success(-1);
    if (numbytes > 0)
    {
        buf[numbytes] = '\0';
        if (ft_strcmp(buf, "fail") == 0)
            handle_fail_success(-1);
        else
            handle_fail_success(0);
    }
    free(file);
}

void    handle_get(int fd, char *str)
{
  ft_putendl("panotobudika chete, gore rino tichafara");
  if ((send(fd, str, ft_strlen(str), 0)) == -1)
        handle_error(6);
}