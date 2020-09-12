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

void			darr_shrink(t_darr *darr)
{
	int			new_cap;
	void		*new_data;

	if (darr->len_data < darr->cap >> 2)
	{
		new_cap = darr->cap >> 1u;
		if (!(new_data = malloc(new_cap * darr->unit_size)))
			return ;
		ft_memmove(new_data, darr->start, darr->len_data * darr->unit_size);
		free(darr->data);
		darr->data = new_data;
		darr->start = new_data;
		darr->cap = new_cap;
	}
}
