/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchrcount.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschimme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 21:35:17 by mschimme          #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

size_t			ft_strchrcount(const char *s, int c)
{
	size_t		amount;
	const char	*bogey;

	amount = 0;
	bogey = s + ft_strlen(s);
	while (*s != '\0')
	{
		if (!(s = (ft_memchr(s, c, bogey - s))))
			s = bogey;
		if (*s && *s == c)
			amount++;
		if (s != bogey)
			s++;
	}
	return (amount);
}
