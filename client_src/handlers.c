#include "../includes/client.h"

void handle_fail_success(int n)
{
	if (n == 0)
	{
		ft_success("********** Server returned SUCCESS *********");
		return;
	}
	ft_err("********** Server returned FAILURE **********");
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
	exit (0);
}

void	ft_err(char *error)
{
	ft_putstr("\033[0;31m");
	ft_putendl(error);
	ft_putstr("\033[0m");
}

void	ft_success(char *msg)
{
	ft_putstr("\033[0;32m");
	ft_putendl(msg);
	ft_putstr("\033[0m");
}