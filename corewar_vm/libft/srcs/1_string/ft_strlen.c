/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 16:36:56 by limry             #+#    #+#             */
/*   Updated: 2020/03/05 13:44:15 by limry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

size_t			ft_strlen(const char *s)
{
	uint64_t	*longword;
	uint8_t		*byte;

	if (!s)
		return (0);
	byte = (uint8_t*)s;
	while ((uint64_t)byte & 7ULL)
	{
		if (*byte == '\0')
			return ((size_t)byte - (size_t)s);
		byte++;
	}
	longword = (uint64_t*)byte;
	while ((((*longword) - MHZERO)
	& ~(*longword) & DHZERO) == FALSE)
		longword++;
	byte = (uint8_t*)longword;
	while (*byte)
		byte++;
	return ((size_t)byte - (size_t)s);
}
