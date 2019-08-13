#include "../includes/ftp.h"

char    *get_ip(struct sockaddr_in *sa)
{
        char *ip;

        ip = malloc(sizeof(char) * INET_ADDRSTRLEN);
        ip = inet_ntoa(sa->sin_addr);
        printf("the piv4 address is %s\n", ip);
        return ip;
}

void     init_struct(struct sockaddr_in *sa, int port)
{
        sa->sin_family = AF_INET;
        sa->sin_port = htons(port);
        sa->sin_addr.s_addr = INADDR_ANY;
        ft_memset(sa->sin_zero, '\0', sizeof(sa));
}


void  sigchild_handler(int s)
{
        (void)s;
        while (waitpid(-1, NULL, WNOHANG) > 0);
}

int   init(char *str)
{
        struct sockaddr_in my_addr;
        struct sockaddr_in their_addr;
        int port;
        int socketfd;
        // char *ip;
        int new_fd;
        socklen_t sin_size;
        struct sigaction sa;
        int yes;
        
        yes = 1;
        port = ft_atoi(str);
        if ((socketfd = socket(PF_INET, SOCK_STREAM, 0)) == -1)
                return (-1);
        if (setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
                return (-1);
        // ip = get_ip(&my_addr);
        init_struct(&my_addr, port);
        if (port > 0)
        {
                if (bind(socketfd, (struct  sockaddr *)&my_addr, INET_ADDRSTRLEN) == -1)
                        return -1;
             // if (connect(socketfd, (struct  sockaddr *)&my_addr, INET_ADDRSTRLEN) == -1)
             //    return -1;
                ft_putendl("Listening..........");
                if (listen(socketfd, BACKLOG) == -1)
                        return (-1);
                sa.sa_handler = sigchild_handler;
                sigemptyset(&sa.sa_mask);
                sa.sa_flags = SA_RESTART;
                if (sigaction(SIGCHLD, &sa, NULL) == -1)
                        return (-1);
                while (1)
                {
                        sin_size = sizeof(their_addr);
                        if ((new_fd  = accept(socketfd, (struct sockaddr *)&their_addr,
                                &sin_size)) == -1 )
                                return (-1);
                        ft_putstr("server: got connection from ");
                        ft_putendl(inet_ntoa(their_addr.sin_addr));
                        if (!fork())
                        {
                                close (socketfd);
                                if (send(new_fd, "Hello world\n", 14, 0) == -1)
                                        return (-1);
                                close(new_fd);
                                exit (0);
                        }
                        close(new_fd);
                }
        }
        return 0;
}

int     main(int argc, char **argv)
{
        if (argc == 1)
        {
                ft_putstr("need some args over here\n");
                return (0);
        }
        else
        {
                init(argv[1]);
                return (0);
        }

}
