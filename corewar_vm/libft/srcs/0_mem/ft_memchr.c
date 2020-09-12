/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 18:01:50 by limry             #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem.h"

void			get_search(uint64_t *lc, uint8_t sc)
{
	*lc = sc;
	*lc |= *lc << 8ULL;
	*lc |= *lc << 16ULL;
	*lc |= *lc << 32ULL;
}

void			*ft_memchr(const void *s, int c, size_t n)
{
	uint8_t		sc;
	uint8_t		*sw;
	uint64_t	lc;
	uint64_t	*lw;

	if (n == 0)
		return (NULL);
	sc = (uint8_t)c;
	get_search(&lc, sc);
	lw = (uint64_t*)s;
	while (n > 7ULL)
	{
		if ((((*lw) - MHZERO) & ~(*lw) & DHZERO) ^ lc)
			break ;
		lw++;
		n -= 8ULL;
	}
	sw = (uint8_t*)lw;
	while (n--)
		if (*sw == sc)
			return (sw);
		else
			sw++;
	return (NULL);
}
