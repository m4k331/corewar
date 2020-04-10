/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 16:37:04 by limry             #+#    #+#             */
/*   Updated: 2020/03/05 13:44:15 by limry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

void				ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	bogey;

	if (s && f)
	{
		bogey = 0;
		while (s[bogey] != '\0')
		{
			f(bogey, &s[bogey]);
			bogey++;
		}
	}
}
