#include "../includes/client.h"

int 	make_connection(int port, char *name)
{
	int socketfd;
	struct hostent *he;
	struct sockaddr_in their_addr;
	char *client_number;
	char buf[100];
	// pid_t pid;

	if ((he = gethostbyname(name)) == NULL)
		handle_error(1);
	if ((socketfd = socket(PF_INET, SOCK_STREAM, 0)) == -1)
		handle_error (2);
	their_addr.sin_family = AF_INET;
	their_addr.sin_port = htons(port);
	their_addr.sin_addr = *((struct in_addr *)he->h_addr);
	ft_memset(their_addr.sin_zero, '\0', sizeof(their_addr.sin_zero));
	if (connect(socketfd, (struct sockaddr *)&their_addr, sizeof(their_addr)) == -1)
		handle_error(2);
	ft_putendl("\033[1;12mConnected to server.....\033[0m");
	ft_memset(buf, '\0', 100);
	if ((recv(socketfd, buf, 100, 0)) != -1)
		client_number = ft_strdup(buf);
	else
	{
		ft_putendl("get client_number failed");
		exit(0);
	}
		while (1)
		{
			read_input(socketfd, client_number);
		}
		free(client_number);
		client_number = NULL;
		// free(name);
		close (socketfd);
	return (0);
}

int	main(int argc, char **argv)
{
	
	int port;

	if (argc == 3)
	{
		port = ft_atoi(argv[2]);
		if (port > 0)
		{
			return (make_connection(port, argv[1]));
		}
		return (0);
	}
	else
	{  
		ft_putendl("Not enough args");
		return (0);
	}
}
