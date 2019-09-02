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

static size_t		word_count(const char *s, char c)
{
	size_t i;
	size_t wdcount;

	i = 0;
	wdcount = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] == '\0')
			return (wdcount);
		while (s[i] != c && s[i])
			i++;
		wdcount++;
	}
	return (wdcount);
}

char				**ft_strsplit(char const *s, char c)
{
	char			**tab;
	char			*str;
	int				t;
	int				n;
	int				i;

	t = 0;
	n = 0;
	str = (char *)s;
	tab = NULL;
	if (s == NULL || ((tab = (char **)malloc(sizeof(char *)
		* (word_count(s, c) + 1))) == NULL)) 
		return (NULL);
	while (t <= word_count(s, c) && str[n])
	{
		while(str[n] && str[n] == c)
			n++;
		i = n;
		while(str[n] && str[n] != c)
			n++;
		tab[t] = ft_strsub(str, i, n - i);
		t++;
	}
	tab[t] = NULL;
	return (tab);
}
