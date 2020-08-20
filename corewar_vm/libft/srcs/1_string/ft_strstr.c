/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 16:36:17 by limry             #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char			*ft_strstr(const char *haystack, const char *needle)
{
	const char	*camel;
	const char	*eye;

	if (*needle == '\0')
		return ((char*)haystack);
	while (*haystack != '\0')
	{
		camel = haystack;
		eye = needle;
		while (*eye != '\0' && *camel == *eye)
		{
			++eye;
			++camel;
		}
		if (*eye == '\0')
			return ((char*)haystack);
		++haystack;
	}
	return (NULL);
}
