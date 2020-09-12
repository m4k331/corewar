/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darr_remove_front.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 15:56:57 by limry             #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_darr.h"

void			darr_del_ith(t_darr *darr, int64_t i,
				int64_t num_units_to_del)
{
	void		*p_del;
	void		*p_from;
	int64_t		size_to_del;
	int64_t		move_size;

	if (i >= darr->len_data)
		return ;
	if (i + num_units_to_del > darr->len_data)
		num_units_to_del = darr->len_data - i;
	p_del = darr->start + i * darr->unit_size;
	size_to_del = num_units_to_del * darr->unit_size;
	p_from = p_del + size_to_del;
	move_size = darr->cap * darr->unit_size - (p_from - darr->data);
	ft_memmove(p_del, p_from, move_size);
	darr->len_data -= num_units_to_del;
	darr->len -= num_units_to_del;
	ft_bzero(darr->data + darr->len * darr->unit_size, size_to_del);
	darr_shrink(darr);
}
