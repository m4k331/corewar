/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darr_pop_front.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 14:58:37 by limry             #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_darr.h"

void			*darr_pop_front(t_darr *darr, void **res, int64_t len_units)
{
	if (!darr)
	{
		ft_putstr_fd("Error: no darr as src\n", 2);
		return (NULL);
	}
	if (!res)
	{
		ft_putstr_fd("Error: no pointer to dst\n", darr->err_fd);
		return (NULL);
	}
	if (len_units <= darr->len_data)
	{
		if (!(*res = malloc(len_units * darr->unit_size)))
		{
			ft_putstr_fd("Error: can't allocate mem for popping units\n",
					darr->err_fd);
			return (NULL);
		}
		*res = ft_memmove(*res, darr->start, len_units * darr->unit_size);
		darr->start += len_units * darr->unit_size;
		darr->len_data -= len_units;
		darr_shrink(darr);
		return (*res);
	}
	return (darr_pop_all(darr, res));
}
