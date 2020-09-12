/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 18:02:09 by limry             #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem.h"

void			*ft_memset(void *b, int c, size_t len)
{
	uint64_t	*lw;
	uint64_t	lc;
	uint8_t		*sw;
	uint8_t		sym;

	lc = (uint8_t)c;
	lc |= lc << 8ULL;
	lc |= lc << 16ULL;
	lc |= lc << 32ULL;
	lw = (uint64_t*)b;
	sym = (uint8_t)c;
	while (len > 7ULL)
	{
		*lw = lc;
		len -= 8ULL;
		lw++;
	}
	sw = (uint8_t*)lw;
	while (len--)
	{
		*sw = sym;
		sw++;
	}
	return (b);
}
