#include "../includes/client.h"

void handle_fail_success(int n)
{
	if (n == 0)
	{
		ft_putendl("\033[1;32m********** Server returned SUCCESS *********\033[0m\033[1;12m");
		return;
	}
	ft_putendl("\033[1;31m********** Server returned FAILURE **********\033[0m");
	exit(0);
}

void		handle_exit(int fd)
{
	close(fd);
	ft_putendl("\033[0;31mConnection successfully closed\033[0m");
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

void		handle_ls(int fd)
{
	int numbytes;
	char *contents;
	char **ls;
	int n;

	n = 0;
	contents = (char *)malloc(sizeof(char) * 1000);
	if ((send(fd, "ls", 2, 0)) == -1)
        handle_error(6);
    if ((numbytes = recv(fd, contents, 999, 0)) == -1)
        handle_fail_success(-1);
    if (numbytes > 0)
    {
    	handle_fail_success(0);
        contents[numbytes] = '\0';
        ls = ft_strsplit(contents, '\n');
        while (ls[n])
        {
        	if (ft_strcmp(ls[n], "temp.txt") != 0)
        	{
        		ft_putstr(ls[n]);
        		ft_putstr(" ");
        	}
        	n++;
        }
        ft_putstr("\n\033[0m");
    }
    free_2d_array((void *)ls);
    free(contents);
}

int		handle_error(int errno)
{
	if (errno == 0)
		ft_putendl("Incorrect number of arguments");
	if (errno == 1)
		ft_putendl("No such host found");
	if (errno == 2)
		ft_putendl("Socket creation failed");
	if (errno == 3)
		ft_putendl("Listening failed");
	if (errno == 4)
		ft_putendl("Signal not found");
	if (errno == 5)
		ft_putendl("Accepting failed");
	if (errno == 6)
		ft_putendl("Sending failed");
	exit (0);
}