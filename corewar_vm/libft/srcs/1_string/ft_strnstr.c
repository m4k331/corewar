/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 16:36:34 by limry             #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char			*ft_strnstr(const char *haystack,
				const char *needle, size_t len)
{
	const char	*camel;
	const char	*eye;
	size_t		cash;

	if (*needle == '\0')
		return ((char*)haystack);
	while (*haystack != '\0' && len != 0)
	{
		camel = haystack;
		eye = needle;
		cash = len;
		while (*eye != '\0' && *camel == *eye && cash != 0)
		{
			++eye;
			++camel;
			--cash;
		}
		if (*eye == '\0')
			return ((char*)haystack);
		++haystack;
		--len;
	}
	return (NULL);
}
