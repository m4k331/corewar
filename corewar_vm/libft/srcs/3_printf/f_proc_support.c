/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_proc_support.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 17:26:38 by limry             #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void				def_big_small_bint(const t_bint *first,
					const t_bint *second, const t_bint **big,
					const t_bint **small)
{
	if (bint_comp(first, second) >= 0)
	{
		*big = first;
		*small = second;
	}
	else
	{
		*big = second;
		*small = first;
	}
}

t_bint				*bint_mult_u32(t_bint *res, t_u32 num)
{
	size_t			i;
	t_u64			lefts;
	t_u64			holder;

	if (num == 1)
		return (res);
	i = 0;
	lefts = 0UL;
	while (i < res->len)
	{
		holder = (t_u64)res->arr[i] * (t_u64)num + lefts;
		res->arr[i] = (t_u32)(holder & (0xFFFFFFFFU));
		lefts = holder >> 32ULL;
		i++;
	}
	if (lefts && i <= DBL_MAX_LEN)
		res->arr[i] = (t_u32)(lefts & 0xFFFFFFFFUL);
	res->len = bint_len(res);
	return (res);
}

t_bint				*bint_add_bint(t_bint *res,
					const t_bint *first, const t_bint *sec)
{
	size_t			len;
	size_t			i;
	t_u64			holder;
	t_u64			lefts;

	len = first->len > sec->len ? first->len : sec->len;
	i = 0;
	lefts = 0;
	while (i < len)
	{
		holder = (lefts + (t_u64)first->arr[i] + (t_u64)sec->arr[i]);
		res->arr[i] = (t_u32)(holder & 0xFFFFFFFFU);
		lefts = holder >> 32ULL;
		i++;
	}
	if (lefts && i < DBL_MAX_LEN)
		res->arr[i] = (t_u32)(lefts & 0xFFFFFFFFUL);
	res->len = bint_len(res);
	return (res);
}

t_bint				*bint_mult_bint(t_bint *res, const t_bint *first,
					const t_bint *second)
{
	const t_bint	*big;
	const t_bint	*small;
	t_bint			tmp;
	size_t			i;
	int				step;

	i = 0;
	step = 0;
	def_big_small_bint(first, second, &big, &small);
	while (i < small->len)
	{
		tmp = (t_bint){0, {0}};
		bint_copy(&tmp, big);
		bint_mult_u32(&tmp, small->arr[i]);
		move_left(&tmp, step * 32UL);
		bint_add_bint(res, &tmp, res);
		i++;
		step++;
	}
	return (res);
}

t_bint				*move_left(t_bint *bint, t_u32 step)
{
	t_u32			i;

	if (!step)
		return (bint);
	i = DBL_MAX_LEN;
	if (!(step % 32))
		while (--i >= step / 32)
			bint->arr[i] = bint->arr[i - (step / 32)];
	else
	{
		while (--i >= (step / 32 + 1))
			bint->arr[i] = ((bint->arr[i - (step / 32 + 1)]) >>
					(32 - (step % 32))) |
							((bint->arr[i - step / 32]) << (step % 32));
		bint->arr[i] = bint->arr[i - step / 32] << (step % 32);
	}
	i = (step % 32) ? i : i + 1;
	while (i--)
		bint->arr[i] = 0;
	bint->len = bint_len(bint);
	return (bint);
}
