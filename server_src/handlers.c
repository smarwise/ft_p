#include "../includes/server.h"

void  sigchild_handler()
{
    // while (waitpid(-1, NULL, WNOHANG) > 0);
    while (wait4(-1, NULL, WNOHANG, NULL) > 0);
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
		ft_putendl("\033[1;31mNo bytes sent\033[0m");
	if (err == 8)
		ft_putendl("\033[1;31mOpen fail\033[0m");
	exit (0);
}

void	send_cmds(char *str, int fd)
{
	char *temp;

	temp = str;
	if (ft_strcmp("pwd", str) == 0)
		show_pwd(fd);
	if (ft_strcmp("ls", str) == 0)
		ls_dir(fd);
	if (ft_strnstr(str, "cd", 2))
		cd_dir(fd, str);
	if (ft_strnstr(str, "put", 3))
		put_file(fd, str);
	if (ft_strnstr(str, "get", 3))
		get_file(fd, str);
	free(temp);
	free(str);
}

void	send_result(int n, int fd)
{
	if (n == -1)
	{
		if ((send(fd, "fail", 4, 0)) == -1)
        	handle_error(6);
	}
	else
	{
		if ((send(fd, "success", 7, 0)) == -1)
        	handle_error(6);
	}
}