/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarwise <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 07:45:42 by smarwise          #+#    #+#             */
/*   Updated: 2019/11/26 07:45:43 by smarwise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

char    *get_ip(struct sockaddr_in *sa)
{
        char *ip;

        ip = malloc(sizeof(char) * INET_ADDRSTRLEN);
        ip = inet_ntoa(sa->sin_addr);
        return ip;
}

int     main(int argc, char **argv)
{
        if (argc == 2)
        {
            init(argv[1]);
            return (0);
        }
        else
            return (handle_error(0));
}
