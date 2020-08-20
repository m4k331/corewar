/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darr_pop_all.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 15:42:17 by limry             #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_darr.h"

void		*darr_pop_all(t_darr *darr, void **res)
{
	if (!darr)
	{
		ft_putstr_fd("Error: no darr as src\n", darr->err_fd);
		return (NULL);
	}
	if (!res)
	{
		ft_putstr_fd("Error: no pointer to dst\n", darr->err_fd);
		return (NULL);
	}
	if (!(*res = malloc(darr->len_data * darr->unit_size)))
	{
		ft_putstr_fd("Error: can't allocate mem for popping all units\n",
				darr->err_fd);
		return (NULL);
	}
	*res = ft_memmove(*res, darr->start, darr->len_data * darr->unit_size);
	ft_bzero(darr->data, darr->cap * darr->unit_size);
	darr->len = 0;
	darr->start = darr->data;
	darr->len_data = 0;
	return (*res);
}
