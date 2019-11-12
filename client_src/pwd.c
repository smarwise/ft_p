#include "../includes/client.h"

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
    }
    free(buf);
    buf = NULL;
}