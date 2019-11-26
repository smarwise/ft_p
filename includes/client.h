/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarwise <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 07:46:08 by smarwise          #+#    #+#             */
/*   Updated: 2019/11/26 07:46:10 by smarwise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
#define CLIENT_H
#include "ftp.h"
#include <fcntl.h>

void		handle_exit(int fd);
void		handle_pwd(int fd);
int   handle_error(int errno);
int   read_input(int fd, char *client_number);
void		handle_ls(int fd);
void handle_fail_success(int n);
void	handle_cd(int fd, char *str);
void    handle_put(int fd, char **file, char *str);
void    handle_get(int fd, char *str);
void	ft_err(char *error);
void	ft_success(char *msg);

#endif