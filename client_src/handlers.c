#include "../includes/client.h"

void handle_fail_success(int n)
{
	if (n == 0)
	{
		ft_putendl("\033[1;32m********** Server returned SUCCESS *********\033[0m\033[1;12m");
		return;
	}
	ft_putendl("\033[1;31m********** Server returned FAILURE **********\033[0m");
	// exit(0);
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
	if (errno == 7)
	{
		ft_putendl("\033[0;31mSelected file does not exist\033[0m");
		return (0);
	}
	exit (0);
}