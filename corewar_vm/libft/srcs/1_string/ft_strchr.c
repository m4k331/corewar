/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 16:37:32 by limry             #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

static inline void	expand_value(uint64_t *w, uint8_t u)
{
	*w = u;
	*w |= *w << 8ULL;
	*w |= *w << 16ULL;
	*w |= *w << 32ULL;
}

char				*ft_strchr(const char *s, int c)
{
	uint64_t		*longword;
	uint8_t			*byte;
	uint64_t		w;
	uint8_t			u;

	u = (unsigned char)c;
	expand_value(&w, u);
	byte = (uint8_t*)s;
	while ((uint64_t)byte & 7ULL)
	{
		if (*byte == '\0')
			return (NULL);
		if (*byte == u)
			return ((char*)byte);
		byte++;
	}
	longword = (uint64_t*)byte;
	while ((((*longword) - MHZERO) & ~(*longword) & DHZERO) == FALSE && \
	(((((*longword) - MHZERO) & ~(*longword) & DHZERO) ^ w)) == FALSE)
		longword++;
	byte = (uint8_t*)longword;
	if (((((*longword) - MHZERO) & ~(*longword) & DHZERO) ^ w) != FALSE)
		while (*byte && *byte != u)
			byte++;
	return (*byte == u ? (char*)byte : NULL);
}
