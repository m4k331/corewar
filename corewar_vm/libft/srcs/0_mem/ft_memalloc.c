/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 18:01:45 by limry             #+#    #+#             */
/*   Updated: 2020/06/05 14:43:34 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem.h"

void		*ft_memalloc(size_t size)
{
	void *pocket;

	if (!(pocket = malloc(size)))
		return (NULL);
	ft_bzero(pocket, size);
	return (pocket);
}
