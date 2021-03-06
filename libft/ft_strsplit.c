/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarwise <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 09:19:49 by smarwise          #+#    #+#             */
/*   Updated: 2018/06/08 17:20:52 by smarwise         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strsplit(char const *s, char c)
{
	char	**str;
	size_t	index;
	size_t	start;
	size_t	wordcount;

	index = 0;
	wordcount = 0;
	if (s == NULL)
		return (NULL);
	str = (char**)ft_memalloc(sizeof(char *) * (ft_delimcountwords(s, c)) + 1);
	if (str == NULL)
		return (NULL);
	while (s[index])
	{
		while ((s[index] == c))
			index++;
		start = index;
		while ((s[index] != c) && (s[index]))
			index++;
		if (index > start)
			str[wordcount++] = ft_strsub(s, start, (index - start));
	}
	str[wordcount] = 0;
	return (str);
}

