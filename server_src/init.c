#include "../includes/server.h"

int    init_struct(struct sockaddr_in *sa, int port, int socketfd)
{
    struct sigaction sig;

	sa->sin_family = AF_INET;
    sa->sin_port = htons(port);
    sa->sin_addr.s_addr = INADDR_ANY;
    ft_memset(sa->sin_zero, '\0', sizeof(sa->sin_zero));
    if (bind(socketfd, (struct  sockaddr *)sa,
        sizeof(*sa)) == -1)
    	return (handle_error(2));
    if (listen(socketfd, BACKLOG) == -1)
    	return (handle_error(3));
    ft_putendl("\033[1;12mListening..........\033[1;0m");
    sig.sa_handler = sigchild_handler;
    sigemptyset(&sig.sa_mask);
    sig.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sig, NULL) == -1)
    {
        ft_putendl("sigaction");
        exit(0);
    }
    // if (signal(1,sigchild_handler) == SIG_ERR)
    //     return (handle_error(4));

    return 0;
}

void    receive_data(int fd)
{
    // char buf[MAXDATASIZE];
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
            ft_putstr("\033[1;34mServer: Command to ");
            ft_putstr(buf);
            ft_putendl(" received\033[1;0m");
            send_cmds(buf, fd);
        }
    }
}

void error(char *msg)
{
    perror(msg);
    exit (1);
}

int	 be_connected(int socketfd, struct sockaddr_in *their_addr)
{ 
	int new_fd;
    socklen_t sin_size;
    int pid;
    
    while (42)
    {
        sin_size = sizeof(*their_addr);
        if ((new_fd  = accept(socketfd,
                (struct sockaddr *)their_addr, &sin_size)) != -1 )
        {
            ft_putstr("\033[1;32mServer: got connection from \033[1;0m");
            ft_putendl(inet_ntoa(their_addr->sin_addr));
            pid = fork();
            if (pid == 0)
            {
                close(socketfd);
                receive_data(new_fd);
                close(new_fd);
                exit(0);
            }
            close(new_fd);
        }
        else
        {
            ft_putendl("Accepting failed");
            exit (0);
        }
    }
    return 0;
}

int   init(char *str)
{
	struct sockaddr_in my_addr;
	struct sockaddr_in their_addr;
	int port;
	int socketfd;
	int yes;

	yes = 1;
    port = ft_atoi(str);
    if (port > 0)
    {
        if ((socketfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    	   return (handle_error(1));
		if (setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR,
			&yes, sizeof(int)) == -1)
			return (handle_error(1));
		init_struct(&my_addr, port, socketfd);
		return (be_connected(socketfd, &their_addr));
	}
	return 0;
}