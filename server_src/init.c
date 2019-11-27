/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarwise <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 07:45:25 by smarwise          #+#    #+#             */
/*   Updated: 2019/11/26 07:45:26 by smarwise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

void    get_client_nu(t_var *var, t_global *globe)
{
    char *tmp;
    char *tmp2;

    tmp = ft_itoa(globe->nb_clients);
    tmp2 = ft_strdup("00");
    var->client_number = ft_strnew(50);
    ft_memset(var->client_number, '\0', 50);
    var->client_number = ft_strcat(tmp2, tmp);
    free(tmp);
    globe->nb_clients++;
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

void    connect_help(struct sockaddr_in *their_addr, t_var *var,\
        int socketfd, t_global *globe)
{
    char *ip;

    ip = get_ip(their_addr);
    get_client_nu(var, globe);
    ft_putstr("\033[1;32mServer: got connection from \033[1;0m(");
    ft_putstr(ip);
    ft_putstr(") [");
    ft_putstr(var->client_number);
    ft_putendl("]");
    if (send(var->fd, var->client_number, ft_strlen(var->client_number), 0) == -1)
    {
        ft_putendl("get client_number failed");
        return ;
    }
    if (!fork())
    {
        close(socketfd);
        if (!var->owd)
            var->owd = get_original_working_dir();
        receive_data(var);
        close(var->fd);
        exit(0);
    }
}

int	 be_connected(int socketfd, struct sockaddr_in *their_addr)
{ 
	int new_fd;
    socklen_t sin_size;
    t_var   *var;
    t_global *globe;

    globe = (t_global*)malloc(sizeof(t_global));
    globe->nb_clients = 0;
    while (42)
    {
        sin_size = sizeof(*their_addr);
        if ((new_fd  = accept(socketfd,
                (struct sockaddr *)their_addr, &sin_size)) != -1 )
        {
            globe->nb_clients++;
            var = (t_var*)malloc(sizeof(t_var));
            var->fd = new_fd;
            var->cmd = NULL;
            var->quit = 0;
            connect_help(their_addr, var, socketfd, globe);
            globe->nb_clients--;
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
