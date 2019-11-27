/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarwise <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 07:45:17 by smarwise          #+#    #+#             */
/*   Updated: 2019/11/26 07:45:18 by smarwise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/server.h"

void  sigchild_handler()
{
    while (wait4(-1, NULL, WNOHANG, NULL) > 0);
}

int		handle_error(int err)
{
	if (err == 0)
		ft_putendl("\033[1;31mIncorrect number of arguments\033[0m");
	if (err == 1)
		ft_putendl("\033[1;31mSocket setup failed\033[0m");
	if (err == 2)
		ft_putendl("\033[1;31mConnecting failed\033[0m");
	if (err == 3)
		ft_putendl("\033[1;31mListening failed\033[0m");
	if (err == 4)
		ft_putendl("\033[1;31mSignal not found\033[0m");
	if (err == 5)
		ft_putendl("\033[1;31mAccepting failed\033[0m");
	if (err == 6)
		ft_putendl("\033[1;31Sending failed\033[0m");
	if (err == 7)
		ft_putendl("\033[1;31mNo bytes sent\033[0m");
	if (err == 8)
		ft_putendl("\033[1;31mOpen fail\033[0m");
	exit (0);
}

void	send_cmds(char *str, int fd, char *client_number, char *owd)
{
	pid_t pid;

	if (ft_strcmp("pwd", str) == 0)
		show_pwd(fd, client_number);
	else if (ft_strstr(str, "ls"))
	{
		pid = fork();
		if (pid == 0)
		{
			ls_dir(fd, client_number, str);
			exit (0);
		}
		else
			wait4(pid, 0, 0, 0);
	}
	else if (ft_strnstr(str, "cd", 2))
		cd_dir(fd, str, client_number);
	else if (ft_strnstr(str, "put", 3))
		put_file(fd, str, client_number, owd);
	else if (ft_strnstr(str, "get", 3))
		get_file(fd, str, client_number);
}

void	send_result(int n, int fd)
{
	if (n == -1)
	{
		if ((send(fd, "fail", 4, 0)) == -1)
        	handle_error(6);
	}
	else
	{
		if ((send(fd, "success", 7, 0)) == -1)
        	handle_error(6);
	}
}

void	print_cmd(char *str, char *client_number)
{
	ft_putstr("Server[");
	ft_putstr(client_number);
	ft_putstr("]: ");
	ft_putstr("\033[1;34mCommand to ");
	ft_putstr(str);
	ft_putendl(" received\033[1;0m");
}

void	print_msg(char *msg, char *client_number)
{
	ft_putstr("Server[");
	ft_putstr(client_number);
	ft_putstr("]: ");
	ft_putendl(msg);
}
