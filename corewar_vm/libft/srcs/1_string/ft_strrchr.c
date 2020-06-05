/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 16:36:32 by limry             #+#    #+#             */
/*   Updated: 2020/06/05 14:43:35 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char		*ft_strrchr(const char *s, int c)
{
	char	*n;
	char	*p;

	n = ft_strchr(s, c);
	p = n;
	while (p)
	{
		n = p;
		p = ft_strchr(n + 1, c);
	}
	return (n);
}
