/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 18:01:53 by limry             #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem.h"

static int	ft_lil_memcmp(size_t *l_s1, size_t *l_s2, size_t n)
{
	uint8_t	*s_s1;
	uint8_t	*s_s2;

	s_s1 = (uint8_t*)l_s1;
	s_s2 = (uint8_t*)l_s2;
	while (n--)
	{
		if (*s_s1 != *s_s2)
			return (*s_s1 - *s_s2);
		s_s1++;
		s_s2++;
	}
	return (0);
}

int			ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	*l_s1;
	size_t	*l_s2;

	if (0 == n || ((const char *)s1 == NULL && (const char *)s2 == NULL))
		return (0);
	l_s1 = (size_t*)s1;
	l_s2 = (size_t*)s2;
	while (n > 7ULL)
	{
		if (*l_s1 != *l_s2)
			break ;
		l_s1++;
		l_s2++;
		n -= 8ULL;
	}
	return (ft_lil_memcmp(l_s1, l_s2, n));
}
