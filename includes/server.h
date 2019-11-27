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

typedef struct s_var
{
    char *cmd;
    int fd;
    int quit;
    char *client_number;
    char *owd;
}               t_var;

typedef struct s_global
{
    int    nb_clients;
}               t_global;

int     init(char *str);
void    sigchild_handler();
int     handle_error(int err);
void	ls_dir(t_var *var, char *str);
void	show_pwd(t_var *var);
void    handle_fail_success(int n);
void    cd_dir(t_var *var, char *str);
void    put_file(t_var *var, char *str);
void    get_file(t_var *var, char *str);
void	send_result(int n, int fd);
char    *get_file_name(char *str, char *files);
void	print_cmd(char *str, char *client_number);
char    *get_ip(struct sockaddr_in *sa);
void	print_msg(char *msg, char *client_number);
void    receive_data(t_var *var);
void    error(char *msg);
char    *get_original_working_dir();
void    quit(t_var *var);
void	send_cmds(char *str, t_var *var);

#endif