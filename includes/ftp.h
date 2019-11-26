/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarwise <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 07:46:28 by smarwise          #+#    #+#             */
/*   Updated: 2019/11/26 07:46:30 by smarwise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTP_H
#define FTP_H
#include "../libft/libft.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/stat.h>
#define BACKLOG 10
#define MAXDATASIZE 1000
#define BUFFSIZE 5

#endif