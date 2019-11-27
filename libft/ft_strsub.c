/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarwise <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 09:51:29 by smarwise          #+#    #+#             */
/*   Updated: 2018/06/11 07:20:14 by smarwise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	index;

	if (s == NULL)
		return (NULL);
	index = 0;
	str = ft_strnew(len);
	if (str == NULL)
		return (NULL);
	while (len-- && s[start])
		str[index++] = s[start++];
	return (str);
}
