/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_proc_support2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 17:28:58 by limry             #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int					bint_div_bint_to_int(const t_bint *dec, const t_bint *div)
{
	int				res;
	t_bint			tmp;

	res = 5;
	tmp = (t_bint){0, {0}};
	bint_mult_u32(bint_copy(&tmp, div), res);
	if (bint_comp(dec, &tmp) > 0)
	{
		while (bint_comp(dec, bint_add_bint(&tmp, div, &tmp)) > 0)
			++res;
		return (!bint_comp(dec, &tmp) ? res + 1 : res);
	}
	if (bint_comp(dec, &tmp) < 0)
	{
		while (bint_comp(dec, bint_minus_bint(&tmp, div, &tmp)) < 0)
			--res;
		return (res - 1);
	}
	return (res);
}

t_bint				*bint_minus_bint(t_bint *res, const t_bint *first,
					const t_bint *second)
{
	const t_bint	*big;
	const t_bint	*small;
	t_u64			tmp;
	t_u32			lefts;
	size_t			i;

	i = 0;
	lefts = 0UL;
	def_big_small_bint(first, second, &big, &small);
	while (i < big->len)
	{
		tmp = big->arr[i] - lefts;
		lefts = (((big->arr[i] > 0) || (!big->arr[i] && !lefts)) &&
				(tmp >= (t_u32)small->arr[i])) ? 0UL : 1UL;
		res->arr[i] = (t_u32)((tmp + ((lefts) ? (1ULL << 32ULL) : 0ULL)
				- (t_u32)small->arr[i]) & 0xFFFFFFFFUL);
		i++;
	}
	res->len = bint_len(res);
	return (res);
}

t_bint				*int_to_bint(t_u64 num, t_bint *bint)
{
	int				i;

	i = 0;
	while (num && i < DBL_MAX_LEN)
	{
		bint->arr[i] = (t_u32)(num & 0xFFFFFFFFUL);
		num >>= 32UL;
		i++;
	}
	bint->len = bint_len(bint);
	return (bint);
}

int					get_exponent(long double value)
{
	int				exp;

	exp = 0;
	if (!value || ((value >= 1) && (value <= 9)))
		return (exp);
	if (value < 0)
		value *= -1;
	if (value >= 10)
	{
		while (value >= 10)
		{
			value /= 10;
			++exp;
		}
		return (exp);
	}
	while (value < 1)
	{
		value *= 10;
		++exp;
	}
	return (-exp);
}
