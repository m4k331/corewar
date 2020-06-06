/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darr_binsearch.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kona <kona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 09:30:44 by kona              #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_darr.h"

void				*darr_bin_search(t_darr *d, void *start_run,
					int64_t len_mem, t_darr_binargs ba)
{
	void			*mid;
	void			*end_run;

	end_run = start_run + len_mem - d->unit_size;
	while (start_run < end_run)
	{
		mid = start_run + (end_run - start_run) / d->unit_size / 2 *
					d->unit_size;
		if (ba.comparator(start_run, ba.to_find) == 0)
			return (start_run);
		if (ba.comparator(mid, ba.to_find) == 0)
		{
			if (mid == start_run + d->unit_size)
				return (mid);
			else
				end_run = mid + d->unit_size;
		}
		else if ((ba.comparator(mid, ba.to_find) < 0) ^ ba.is_desc)
			start_run = mid + d->unit_size;
		else
			end_run = mid;
	}
	return (start_run);
}
