#include "../includes/client.h"

void show_output(char *contents)
{
	char **ls;
	int n;
	int i;

	n = 1;
	i = 0;
	handle_fail_success(0);
    ls = ft_strsplit(contents, '\n');
    while (ls[0][i] != ' ')
    	i++;
    ft_putstr(ls[0] + i + 1);
    ft_putchar(' ');
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
    free_2d_array((void *)ls);
}

char 		*receive_all(int fd)
{
	int buflen;
	char *buf;
	char *tmp;
	int numbytes;
	int total;

	numbytes = 0;
	total = 0;
	tmp = (char *)malloc(sizeof(char) * 1000);
	if ((numbytes = recv(fd, tmp, 999, 0)) != -1)
	    tmp[numbytes] = '\0';
	else
		handle_fail_success(-1);
	buflen = ft_atoi(tmp);
	buf = (char *)malloc(sizeof(char) * (buflen + 1));
	total += numbytes;
	buf = ft_strcat(buf, tmp);
	while (total < buflen)
	{
		numbytes = recv(fd, tmp, 999, 0);
		if (numbytes == -1)
			handle_fail_success(-1);
		tmp[numbytes] = '\0';
	    buf = ft_strcat(buf, tmp);
	    total += numbytes;
	}
	return(buf);
}

void		handle_ls(int fd)
{
	char *contents;

	if ((send(fd, "ls", 2, 0)) == -1)
        handle_error(6);
    contents = receive_all(fd);
	show_output(contents);
    free(contents);
}