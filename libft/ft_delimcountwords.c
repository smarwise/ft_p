/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delimcountwords.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarwise <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 07:49:02 by smarwise          #+#    #+#             */
/*   Updated: 2019/11/27 07:49:03 by smarwise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_delimcountwords(const char *s, char c)
{
	size_t	index;
	size_t	wordcount;
    
	index = 0;
	wordcount = 0;
	if (s != NULL)
	{
		while (s[index])
		{
			while ((s[index] == c) && (s[index] != '\0'))
				index++;
			if ((s[index] != c) && (s[index] != '\0'))
				wordcount++;
			while ((s[index] != c) && (s[index] != '\0'))
				index++;
		}
		return (wordcount);
	}
	return ((size_t)NULL);
}