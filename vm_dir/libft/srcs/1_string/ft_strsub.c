/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 16:36:01 by limry             #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char		*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*sub_s;

	if (!s || !(sub_s = ft_strnew(len)))
		return (NULL);
	s = s + start;
	ft_memcpy((void *)sub_s, (const void *)s, len);
	return (sub_s);
}
