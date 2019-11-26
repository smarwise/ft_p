#include "../includes/server.h"

void    receive_data(int fd, char *client_number, char *owd)
{
    int     numbytes;
    char *buf;

    buf = (char *)malloc(sizeof(char) * MAXDATASIZE);
    while (1)
    {
        if ((numbytes = recv(fd, buf, MAXDATASIZE-1, 0)) == -1)
            numbytes = 0;
        if (numbytes > 0)
        {
            buf[numbytes] = '\0';
            send_cmds(buf, fd, client_number, owd);
        }
    }
}

void error(char *msg)
{
    perror(msg);
    exit (1);
}

char		*get_original_working_dir()
{
	char *owd;
		
	owd = (char *)malloc(sizeof(char) * FILENAME_MAX);
	getcwd(owd, FILENAME_MAX);
	return (owd);
}