/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 16:36:28 by limry             #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

static void		ft_clearall(char **res, size_t endpos)
{
	if (endpos != 0)
		while (--endpos > 0)
		{
			free(res[endpos]);
			res[endpos] = NULL;
		}
	free(res);
	res = NULL;
}

static char		*ft_returnword(size_t wbeg, const char *s, char c)
{
	char	*word;
	size_t	wl;

	wl = wbeg;
	while (s[wl] != c && s[wl] != '\0')
		wl++;
	word = (char*)malloc(wl - wbeg);
	if (word == NULL)
		return (NULL);
	word = ft_strncpy(word, &s[wbeg], wl - wbeg);
	return (word);
}

static char		**ft_splitter(char **res, char const *s, char c)
{
	size_t			i;
	char			*word;
	size_t			pos;

	i = 0;
	pos = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != c && s[i] != '\0')
		{
			if (!(word = ft_returnword(i, s, c)))
				ft_clearall(res, pos);
			if (!res)
				return (NULL);
			res[pos++] = word;
		}
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	res[pos] = NULL;
	return (res);
}

char			**ft_strsplit(char const *s, char c)
{
	size_t			i;
	size_t			size;
	char			**res;

	if (!s)
		return (NULL);
	i = 0;
	size = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != c && s[i] != '\0')
			size++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	res = (char**)malloc(sizeof(char*) * size + 1);
	if (!res)
		return (NULL);
	return (ft_splitter(res, s, c));
}
