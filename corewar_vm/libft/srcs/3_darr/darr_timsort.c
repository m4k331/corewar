/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darr_timsort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kona <kona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 09:10:13 by kona              #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_darr.h"

uint32_t			timsort_min_run_length(uint32_t n)
{
	uint32_t	flag;

	flag = 0;
	while (n >= 64)
	{
		flag |= n & 1u;
		n >>= 1u;
	}
	return (n + flag);
}

static void			ft_darr_timsort_init(t_darr *darr,
					int (comparator)(void *a, void *b), int64_t minrun_mem)
{
	t_timsort		stack[darr->len_data / (minrun_mem / darr->unit_size)];
	int64_t			istack;
	int64_t			run_start;

	istack = 0;
	run_start = 0;
	while (run_start < darr->len_data * (int64_t)darr->unit_size)
	{
		stack[istack].data = darr->start + run_start;
		stack[istack].len = darr_timsort_getrun(darr, stack[istack].data,
					minrun_mem, comparator);
		run_start += stack[istack].len;
		istack++;
		merge_instant(darr, &istack, stack, comparator);
	}
	while (istack > 1)
	{
		stack[istack - 2].len = ft_merge_batches(darr,
					stack[istack - 2], stack[istack - 1], comparator);
		istack--;
	}
}

void				ft_darr_timsort(t_darr *darr,
					int (comparator)(void *a, void *b))
{
	if (darr->len_data < 2 || !comparator)
		return ;
	ft_darr_timsort_init(darr, comparator,
			timsort_min_run_length(darr->len_data) * darr->unit_size);
}
