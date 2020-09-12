/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darr_timsort_getrun.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kona <kona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 09:34:48 by kona              #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_darr.h"

static void			move_data(void *i1, unsigned long len_i1,
					void *i2, size_t len_i2)
{
	uint8_t			tmp[len_i2];

	ft_memmove(tmp, i2, len_i2);
	ft_memmove(i1 + len_i2, i1, len_i1);
	ft_memmove(i1, tmp, len_i2);
}

static int64_t		bucket(t_darr *darr, void *start_run, int64_t minrun_mem,
					t_darr_binargs ba)
{
	int64_t			len_batch;
	int64_t			max_len;
	void			*i1;
	void			*i2;

	len_batch = 2 * darr->unit_size;
	max_len = darr->len_data * darr->unit_size - (start_run - darr->start);
	i2 = start_run + darr->unit_size;
	while (len_batch < max_len)
	{
		i1 = i2;
		i2 = i2 + darr->unit_size;
		if ((ba.comparator(i1, i2) < 0) ^ ba.is_desc)
			len_batch += darr->unit_size;
		else if (len_batch >= minrun_mem)
			return (len_batch);
		else
		{
			ba.to_find = i2;
			i1 = darr_bin_search(darr, start_run, i2 - start_run, ba);
			move_data(i1, i2 - i1, i2, darr->unit_size);
			len_batch += darr->unit_size;
		}
	}
	return (len_batch);
}

static void			bucket_reverse(t_darr *d, void *start_batch,
					int64_t len_batch)
{
	void			*end_batch;
	uint8_t			tmp[d->unit_size];

	end_batch = start_batch + len_batch - d->unit_size;
	while (start_batch < end_batch)
	{
		ft_memmove(tmp, start_batch, d->unit_size);
		ft_memmove(start_batch, end_batch, d->unit_size);
		ft_memmove(end_batch, tmp, d->unit_size);
		start_batch += d->unit_size;
		end_batch -= d->unit_size;
	}
}

int64_t				darr_timsort_getrun(t_darr *darr, void *start_run,
					int64_t minrun_mem, int (*compare)(void *, void *))
{
	int64_t			len_batch;
	t_darr_binargs	ba;

	ba.comparator = compare;
	ba.is_desc = compare(start_run, start_run + darr->unit_size) > 0;
	len_batch = bucket(darr, start_run, minrun_mem, ba);
	if (!ba.is_desc)
		bucket_reverse(darr, start_run, len_batch);
	return (len_batch);
}
