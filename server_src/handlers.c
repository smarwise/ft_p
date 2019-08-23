#include "../includes/server.h"

void  sigchild_handler()
{
    while (waitpid(-1, NULL, WNOHANG) > 0);
    // while (wait(-1, NULL, WNOHANG, NULL) > 0);
}

int		handle_error(int err)
{
	if (err == 0)
		ft_putendl("Incorrect number of arguments");
	if (err == 1)
		ft_putendl("Socket setup failed");
	if (err == 2)
		ft_putendl("Connecting failed");
	if (err == 3)
		ft_putendl("Listening failed");
	if (err == 4)
		ft_putendl("Signal not found");
	if (err == 5)
		ft_putendl("Accepting failed");
	if (err == 6)
		ft_putendl("Sending failed");
	exit (0);
}

void	send_cmds(char *str, int fd)
{
	if (ft_strcmp("pwd", str) == 0)
		show_pwd(fd);
	if (ft_strcmp("ls", str) == 0)
		ls_dir(fd);
}

