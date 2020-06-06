/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 18:01:56 by limry             #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem.h"

void				*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			*lsub_dst;
	const size_t	*lsub_src;
	uint8_t			*srt_dst;
	const uint8_t	*srt_src;

	if (0 == n || dst == src)
		return (dst);
	lsub_dst = (size_t*)dst;
	lsub_src = (size_t*)src;
	while (n > 7ULL)
	{
		*lsub_dst++ = *lsub_src++;
		n -= 8ULL;
	}
	srt_dst = (uint8_t*)lsub_dst;
	srt_src = (uint8_t*)lsub_src;
	while (n--)
		*srt_dst++ = *srt_src++;
	return (dst);
}
