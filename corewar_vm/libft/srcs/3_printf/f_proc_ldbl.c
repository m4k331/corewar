/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_proc_ldbl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 16:48:41 by limry             #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char				*f_proc(long double arg, t_rules *rules)
{
	t_dbl			arg_double;
	t_s32			exp;
	char			*res;
	char			*digits;

	if (rules->mod & 32ULL)
		arg_double.dlong = arg;
	else
		arg_double.d = arg;
	exp = 0;
	if (rules->mod & 32ULL)
		rules->sign = arg_double.t_dblp.sign ? -1 : 1;
	else
		rules->sign = arg_double.t_parts.sign ? -1 : 1;
	if (f_handle_extremums(arg_double, rules, &res))
		return (res);
	if (rules->mod & 32ULL)
		arg_double.dlong = arg_double.dlong * rules->sign;
	else
		arg_double.d = arg_double.d * rules->sign;
	if (!(digits = ft_strnew(DBL_BUFFER)))
		return (NULL);
	!arg ? digits[0] = '0' : f_proc_dec(arg_double, rules, digits, &exp);
	res = handle_prec(digits, rules, ++exp);
	return (res);
}

static void			calc_parts_dbl(t_s32 *exp, t_u64 *mant,
					t_rules *rules, t_dbl dbl)
{
	if (rules->mod & 32ULL)
	{
		*exp = (t_s32)(dbl.t_dblp.exponent - 16383 - 63 +
				(dbl.t_dblp.exponent ? 0 : 1));
		*mant = (t_u64)(dbl.t_dblp.mantisa +
				(dbl.t_dblp.exponent ? (1ULL << 63ULL) : 0ULL));
	}
	else
	{
		*exp = (t_s32)(dbl.t_parts.exponent - 1023 - 52 +
				(dbl.t_parts.exponent ? 0 : 1));
		*mant = (t_u64)(dbl.t_parts.mantisa +
				(dbl.t_parts.exponent ? (1ULL << 52ULL) : 0ULL));
	}
}

static void			init_parts(t_bint *dec, t_bint *div,
					t_rules *rules, t_dbl dbl)
{
	t_s32			exp;
	t_u64			mant;

	exp = 0U;
	mant = 0ULL;
	calc_parts_dbl(&exp, &mant, rules, dbl);
	int_to_bint(mant, dec);
	int_to_bint(1, div);
	if (exp >= 0)
		move_left(dec, exp);
	else
		move_left(div, -exp);
}

static void			normalize_dec(t_bint *dec, t_bint *div, int exp)
{
	t_bint			tmp;
	t_bint			pow10;

	tmp = (t_bint){0, {0}};
	pow10 = (t_bint){0, {0}};
	if (exp < 0)
	{
		bint_mult_powten(&pow10, -exp);
		bint_mult_bint(&tmp, dec, &pow10);
		*dec = (t_bint) {0, {0}};
		bint_copy(dec, &tmp);
	}
	else if (exp > 0)
	{
		bint_mult_powten(&pow10, exp);
		bint_mult_bint(&tmp, div, &pow10);
		*div = (t_bint) {0, {0}};
		bint_copy(div, &tmp);
	}
}

void				f_proc_dec(t_dbl dbl, t_rules *rules, char *res, int *exp)
{
	t_bint			dec;
	t_bint			div;
	t_bint			tmp;
	size_t			i;
	int				digit;

	dec = (t_bint){0, {0}};
	div = (t_bint){0, {0}};
	init_parts(&dec, &div, rules, dbl);
	get_exp_first_digit(dbl, exp, rules);
	normalize_dec(&dec, &div, *exp);
	i = 0;
	while (i < DBL_MAX_LEN && dec.len > 0)
	{
		digit = bint_div_bint_to_int(&dec, &div);
		res[i] = '0' + digit;
		tmp = (t_bint){0, {0}};
		bint_copy(&tmp, &div);
		bint_mult_u32(&tmp, digit);
		bint_minus_bint(&dec, &tmp, &dec);
		bint_mult_u32(&dec, 10UL);
		++i;
	}
}
