/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 16:36:38 by limry             #+#    #+#             */
/*   Updated: 2020/06/05 14:43:35 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

size_t		ft_strnlen(const char *str, size_t maxlen)
{
	size_t	len;

	len = 0;
	while (len < maxlen)
	{
		if (!*str)
			break ;
		len++;
		str++;
	}
	return (len);
}
