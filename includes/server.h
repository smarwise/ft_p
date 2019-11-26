/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarwise <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 07:46:16 by smarwise          #+#    #+#             */
/*   Updated: 2019/11/26 07:46:18 by smarwise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
#define SERVER_H

#include "ftp.h"
#include <dirent.h>
#include <fcntl.h>

int     init(char *str);
void    sigchild_handler();
int     handle_error(int err);
void	ls_dir(int fd, char *client_number, char *str);
void	show_pwd(int fd, char *client_number);
void	send_cmds(char *str, int fd, char *client_number, char *owd);
void    handle_fail_success(int n);
void    cd_dir(int fd, char *str, char *client_number);
void    put_file(int fd, char *str, char *client_number, char *owd);
void    get_file(int fd, char *str, char *client_number, char *owd);
void	send_result(int n, int fd);
char    *get_file_name(char *str, char *files);
void	print_cmd(char *str, char *client_number);
char    *get_ip(struct sockaddr_in *sa);
void	print_msg(char *msg, char *client_number);
void    receive_data(int fd, char *client_number, char *owd);
void    error(char *msg);
char    *get_original_working_dir();

#endif