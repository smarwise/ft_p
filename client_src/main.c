#include "../includes/ftp.h"

int	main(int argc, char **argv)
{
	int socketfd;
	char buf[MAXDATASIZE];
	struct hostent *he;
	struct sockaddr_in their_addr;
	int port;
	int numbytes;


	if (argc == 3)
	{
		port = ft_atoi(argv[2]);
		if (port > 0)
		{
			if ((he = gethostbyname(argv[1])) == NULL)
				return (0);
			if ((socketfd = socket(PF_INET, SOCK_STREAM, 0)) == -1)
				return (0);
			their_addr.sin_family = AF_INET;
	        their_addr.sin_port = htons(port);
	        their_addr.sin_addr.s_addr = INADDR_ANY;
	        ft_memset(their_addr.sin_zero, '\0', sizeof(their_addr));
			if (connect(socketfd, (struct sockaddr *)&their_addr, sizeof(their_addr)) == -1)
				return(0);
			ft_putendl("Connected to server.....");
			if ((numbytes = recv(socketfd, buf, MAXDATASIZE-1, 0)) == -1)
				return (0);
			ft_putstr("Received info: ");
			ft_putendl(buf);
			close (socketfd);
		}
		return (0);
	}
	else
	{  
		ft_putendl("Not enough args");
		return (0);
	}
}
