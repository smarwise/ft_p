#include "../includes/server.h"

char    *get_client_nu()
{
    static int i = 1;
    char *client_number;
    char *tmp;
    char tmp2[2] = "00";

    tmp = ft_itoa(i);
    client_number = ft_strjoin(tmp2, tmp);
    free(tmp);
    i++;
    return (client_number);
}

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
    if (signal(1,sigchild_handler) == SIG_ERR)
        return (handle_error(4));
    return 0;
}

void    receive_data(int fd, char *client_number)
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
            send_cmds(buf, fd, client_number);
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
    // int pid;
    char *ip;
    char *client_number;
    
    while (42)
    {
        sin_size = sizeof(*their_addr);
        if ((new_fd  = accept(socketfd,
                (struct sockaddr *)their_addr, &sin_size)) != -1 )
        {
            ip = get_ip(their_addr);
            client_number = get_client_nu();
            ft_putstr("\033[1;32mServer: got connection from \033[1;0m(");
            ft_putstr(ip);
            ft_putstr(") [");
            ft_putstr(client_number);
            ft_putendl("]");
            if (send(new_fd, client_number, ft_strlen(client_number), 0) == -1)
            {
                ft_putendl("get client_number failed");
                return -1;
            }
            // pid = fork();
            if (!fork())
            {
                close(socketfd);
                receive_data(new_fd, client_number);
                close(new_fd);
                exit(0);
            }
            // else
            // {
            //     wait4(pid, 0, 0, 0);
            //     close(new_fd);
            //     // exit(0);
            // }
        }
        else
        {
            ft_putendl("Accepting failed");
            exit (0);
        }
    }
    // free(ip);
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