/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 18:01:48 by limry             #+#    #+#             */
/*   Updated: 2020/03/05 13:44:15 by limry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem.h"

void		*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	void	*wrd;
	uint8_t	logos;

	logos = (uint8_t)c;
	if (n == 0)
		return (NULL);
	wrd = (uint8_t*)ft_memchr(src, logos, n);
	if (!wrd)
	{
		ft_memcpy(dst, src, n);
		return (NULL);
	}
	else
		return (ft_memcpy(dst, src, (wrd - src) + 1) + (wrd - src) + 1);
}
