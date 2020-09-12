/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darr_join.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 14:18:07 by limry             #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_darr.h"

static void		darr_expand(t_darr *darr, int64_t len_units,
				size_t unit_size, void *data)
{
	int64_t		new_cap;
	void		*new;

	new_cap = darr->cap;
	while (new_cap <= len_units + darr->len)
		new_cap <<= 1;
	if (!(new = malloc(unit_size * new_cap)))
	{
		ft_putstr_fd("Error: can't alloc size of data for darr\n",
			darr->err_fd);
		return ;
	}
	ft_bzero(new, unit_size * new_cap);
	if (darr->data)
		ft_memcpy(new, darr->start, darr->len_data * darr->unit_size);
	ft_memcpy(new + darr->len_data * unit_size, data, unit_size * len_units);
	free(darr->data);
	darr->data = new;
	darr->cap = new_cap;
	darr->start = darr->data;
	darr->len_data = darr->len_data + len_units;
	darr->len = darr->len_data;
}

static void		darr_simple_join(t_darr *darr, int64_t len_units, void *data)
{
	ft_memcpy(darr->start + darr->len_data * darr->unit_size,
			data, len_units * darr->unit_size);
	darr->len += len_units;
	darr->len_data += len_units;
}

t_darr			*darr_join(t_darr *darr, void *data,
				int64_t len_units, size_t unit_size)
{
	if (!data || !darr)
		return (darr);
	if (unit_size == 0 || unit_size != darr->unit_size)
	{
		ft_putstr_fd("Error: data sizes(!) are not compliant\n", darr->err_fd);
		return (darr);
	}
	if (len_units + darr->len >= darr->cap)
	{
		if (len_units < darr->len - darr->len_data)
		{
			ft_memmove(darr->data, darr->start,
					darr->len_data * darr->unit_size);
			darr->start = darr->data;
			ft_memcpy(darr->data + darr->len_data * darr->unit_size,
					data, len_units * unit_size);
			darr->len_data += len_units;
			darr->len = darr->len_data;
		}
		else
			darr_expand(darr, len_units, unit_size, data);
		return (darr);
	}
	darr_simple_join(darr, len_units, data);
	return (darr);
}
