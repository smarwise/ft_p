/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarwise <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 07:45:07 by smarwise          #+#    #+#             */
/*   Updated: 2019/11/26 07:45:08 by smarwise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

void	show_pwd(int fd, char *client_number)
{
	char *path;

    print_cmd("pwd", client_number);
	path = (char *)malloc(sizeof(char) * FILENAME_MAX);
	if ((getcwd(path, FILENAME_MAX)) == NULL)
    {
        print_msg("\033[1;31mpwd was a FAILURE\033[0m", client_number);
        if ((send(fd, "fail", 4, 0)) == -1)
            print_msg("\033[1;32mfailed to send fail message\033[0m", client_number);
        exit(0);
    }
	if ((send(fd, path, ft_strlen(path), 0)) != -1)
        print_msg("\033[1;32mpwd was a SUCCESS\033[0m", client_number);
    else
        print_msg("\033[1;31mpwd was a FAILURE\033[0m", client_number);
    // free(path);
}

void    cd_dir(int fd, char *str, char *client_number)
{
    char **cmd;

    print_cmd(str, client_number);
    cmd = ft_strsplit(str, ' ');
    if (chdir(cmd[1]) == 0)
    {
        print_msg("\033[0;33mDirectory change success\033[0m", client_number);
        if (send(fd, "success", 7, 0) == -1)
            handle_error(6);
    }
    else
    {
        print_msg("\033[0;31mDirectory change failed\033[0m", client_number);
        if (send(fd, "fail", 4, 0) == -1)
            handle_error(6);
    }
}

void    get_file(int fd, char *str, char *client_number)
{
    char *file_name;
    int fd1;
    char buf[1000];
    int numbytes;

    print_cmd(str, client_number);
    file_name = get_file_name(str);
    if ((fd1 = open(file_name, O_RDONLY)) == -1)
    {
        print_msg("\033[1;31mFail: no such file exits in server\033[0m", client_number);
        send_result(-1, fd);
    }
    while ((numbytes = read(fd1, buf, 1000)) > 0)
    {
        if ((send(fd, buf, numbytes, 0)) == -1)
        {
            print_msg("\033[1;31mFail: no such file exits in server\033[0m", client_number);
            send_result(-1, fd);
        }
    }
    // free(file_name);
    print_msg("\033[1;32mGet file successful\033[0m", client_number);
    close(fd1);
}
