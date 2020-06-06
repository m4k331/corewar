/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_proc_powten.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 16:53:04 by limry             #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static const t_u32		g_pow10_light[8] =
{
	1, 10, 100, 1000, 10000, 100000, 1000000, 10000000
};
static const t_bint		g_pow10_heavy[6] =
{
	{1, {100000000}},
	{2, {0x6fc10000, 0x002386f2}},
	{4, {0x00000000, 0x85acef81, 0x2d6d415b, 0x000004ee}},
	{7, {0x00000000, 0x00000000, 0xbf6a1f01, 0x6e38ed64,
			0xdaa797ed, 0xe93ff9f4, 0x00184f03}},
	{14, {0x00000000, 0x00000000, 0x00000000, 0x00000000,
			0x2e953e01, 0x03df9909, 0x0f1538fd, 0x2374e42f,
			0xd3cff5ec, 0xc404dc08, 0xbccdb0da, 0xa6337f19,
			0xe91f2603, 0x0000024e}},
	{27, {0x00000000, 0x00000000, 0x00000000, 0x00000000,
			0x00000000, 0x00000000, 0x00000000, 0x00000000,
			0x982e7c01, 0xbed3875b, 0xd8d99f72, 0x12152f87,
			0x6bde50c6, 0xcf4a6e70, 0xd595d80f, 0x26b2716e,
			0xadc666b0, 0x1d153624, 0x3c42d35a, 0x63ff540e,
			0xcc5573c0, 0x65f9ef17, 0x55bc28f2, 0x80dcc7f7,
			0xf46eeddc, 0x5fdcefce, 0x000553f7}}};

static void				power10_tu32(t_bint *result, t_u32 exp)
{
	t_bint				tmp;
	t_u32				count;
	t_u32				i;

	count = 1U << 1U;
	while (exp)
	{
		if (exp & 1U)
		{
			i = 0;
			while (i < count)
			{
				tmp = (t_bint){0, {0}};
				bint_mult_bint(&tmp, result, &g_pow10_heavy[5]);
				*result = (t_bint){0, {0}};
				bint_copy(result, &tmp);
				i++;
			}
		}
		exp >>= 1U;
		count <<= 1U;
	}
}

void					bint_mult_powten(t_bint *res, t_u32 exp)
{
	t_bint				tmp;
	t_u32				power;

	if (exp & 0x7U)
		int_to_bint(g_pow10_light[exp & 0x7U], res);
	else
		int_to_bint(1U, res);
	exp >>= 3U;
	power = 0;
	while (exp && power < 6)
	{
		if (exp & 1U)
		{
			tmp = (t_bint){0, {0}};
			bint_mult_bint(&tmp, res, &g_pow10_heavy[power]);
			*res = (t_bint){0, {0}};
			bint_copy(res, &tmp);
		}
		exp >>= 1U;
		++power;
	}
	if (exp)
		power10_tu32(res, exp);
}
