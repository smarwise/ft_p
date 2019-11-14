/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarwise <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 14:17:49 by smarwise          #+#    #+#             */
/*   Updated: 2019/11/14 14:19:05 by smarwise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/client.h"

void		handle_cd(int fd, char *str)
{
	int		numbytes;
	char	buf[20];

	numbytes = 0;
	ft_memset(buf, '\0', 20);
	if ((send(fd, str, ft_strlen(str), 0)) == -1)
		handle_error(6);
	if ((numbytes = recv(fd, buf, 19, 0)) == -1)
		handle_fail_success(-1);
	if (numbytes > 0)
	{
		if (ft_strcmp(buf, "fail") == 0)
			handle_fail_success(-1);
		else
			handle_fail_success(0);
	}
}
