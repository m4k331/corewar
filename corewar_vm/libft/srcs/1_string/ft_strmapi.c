/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 16:36:52 by limry             #+#    #+#             */
/*   Updated: 2020/03/05 13:44:15 by limry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char		*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	szt;
	char	*new;

	if (!s || !f)
		return (NULL);
	szt = 0;
	if (!(new = ft_strnew(ft_strlen(s))))
		return (NULL);
	while (s[szt] != '\0')
	{
		new[szt] = f(szt, s[szt]);
		szt++;
	}
	return (new);
}
