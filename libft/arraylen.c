/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arraylen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarwise <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 11:02:44 by smarwise          #+#    #+#             */
/*   Updated: 2018/07/23 11:03:02 by smarwise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int			arraylen(char **array)
{
	int		i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}
