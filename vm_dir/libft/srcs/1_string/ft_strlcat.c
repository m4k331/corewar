/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 16:36:59 by limry             #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	ldst;
	size_t	lsrc;

	ldst = 0;
	lsrc = ft_strlen(src);
	while (*dst++ && size && ++ldst)
		--size;
	if (size <= 1)
		return (ldst + lsrc);
	while (--size && *src)
		*(dst++ - 1) = *src++;
	*--dst = 0;
	return (ldst + lsrc);
}
