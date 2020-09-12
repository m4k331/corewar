/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 16:36:46 by limry             #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char		*ft_strncpy(char *dst, const char *src, size_t len)
{
	char	*sub_res;

	sub_res = dst;
	while (*src != '\0' && 0 < len)
	{
		*dst++ = *src++;
		--len;
	}
	while (0 < len)
	{
		*dst++ = '\0';
		--len;
	}
	return (sub_res);
}
