#include "../includes/server.h"

void  sigchild_handler()
{
    while (waitpid(-1, NULL, WNOHANG) > 0);
    // while (wait(-1, NULL, WNOHANG, NULL) > 0);
}

int		handle_error(int err)
{
	if (err == 0)
		ft_putendl("\033[1;31mIncorrect number of arguments\033[0m");
	if (err == 1)
		ft_putendl("\033[1;31mSocket setup failed\033[0m");
	if (err == 2)
		ft_putendl("\033[1;31mConnecting failed\033[0m");
	if (err == 3)
		ft_putendl("\033[1;31mListening failed\033[0m");
	if (err == 4)
		ft_putendl("\033[1;31mSignal not found\033[0m");
	if (err == 5)
		ft_putendl("\033[1;31mAccepting failed\033[0m");
	if (err == 6)
		ft_putendl("\033[1;31Sending failed\033[0m");
	if (err == 7)
		ft_putendl("\033[1;31m     No bytes sent\033[0m");
	exit (0);
}

void	send_cmds(char *str, int fd)
{
	if (ft_strcmp("pwd", str) == 0)
		show_pwd(fd);
	if (ft_strcmp("ls", str) == 0)
		ls_dir(fd);
}

