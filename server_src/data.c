#include "../includes/server.h"

void    receive_data(t_var *var, t_global *globe)
{
    int     numbytes;
    char *buf;

    buf = (char *)malloc(sizeof(char) * MAXDATASIZE);
    while (var->quit == 0)
    {
        if ((numbytes = recv(var->fd, buf, MAXDATASIZE-1, 0)) == -1)
            numbytes = 0;
        if (numbytes > 0)
        {
            buf[numbytes] = '\0';
            send_cmds(buf, var, globe);
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