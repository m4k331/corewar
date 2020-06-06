/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 21:23:32 by limry             #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void						ft_filldec_long(char *str, unsigned long num,
								long long dec, t_rules *rules)
{
	long long					len_num;

	len_num = rules->len_num;
	while (dec != 0 && len_num)
	{
		str[--dec] = '0' + num % 10;
		num /= 10;
		len_num--;
	}
	while (dec-- > (rules->flags & 16 || rules->flags & 8 ||
	rules->sign == -1) && !(rules->flags & 4) && (rules->flags & 2))
		str[dec] = '0';
	if (rules->sign < 0 || rules->flags & 16)
		str[dec] = rules->sign < 0 ? '-' : '+';
	else if (rules->flags & 8)
		str[dec] = ' ';
}

static void						ft_fillprec_long(char **str, long double num,
								long long dec, t_rules *rules)
{
	long double					stp;
	long double					num_res;
	long long					prec;

	stp = 10.0;
	prec = (size_t)rules->prec;
	if (rules->flags & 1 || rules->prec)
		(*str)[dec++] = '.';
	while (rules->prec)
	{
		(*str)[dec++] = ((unsigned long long)(num * stp) % 10) + '0';
		rules->prec--;
		stp *= 10;
	}
	num_res = (unsigned long long)((num * (stp / 10) -
			(unsigned long long)(num * (stp / 10))) * 10);
	if (num_res > 4ULL)
		pf_rounding(str, --dec, rules, prec);
	while (++dec < rules->len_word && rules->prec--)
		(*str)[dec] = '0';
}

static size_t					pf_setstart_f(t_rules *rules, long long *start)
{
	long long					len_sign;
	long long					len_dot;

	len_sign = ((rules->sign < 0) || rules->flags & 16 || rules->flags & 8);
	len_dot = (rules->prec || rules->flags & 1);
	if (!(rules->flags & 4))
	{
		if (rules->len_num + rules->prec + len_sign + len_dot > rules->width)
		{
			*start = rules->len_num + len_sign;
			return (rules->len_num + rules->prec + len_sign + len_dot);
		}
		else
		{
			*start = rules->width - (rules->prec + len_dot);
			return (rules->width);
		}
	}
	else
	{
		*start = rules->len_num + len_sign;
		return (rules->len_num + rules->prec + len_sign + len_dot);
	}
}

char							*ft_dtoa(long double num, t_rules *rules)
{
	long long					start;
	long long					fin;
	char						*res;
	unsigned long long			num_aux;
	t_dbl						flt;

	flt.d = num;
	rules->len_num = 1;
	rules->prec = rules->prec_on ? rules->prec : 6;
	rules->sign = flt.t_parts.sign ? -1 : 1;
	if (handle_extremums(num, &res, rules))
		return (res);
	num_aux = (unsigned long long)(num * rules->sign);
	while (num_aux /= 10)
		rules->len_num++;
	fin = pf_setstart_f(rules, &start);
	rules->len_word = (fin > rules->width ? fin : rules->width);
	res = (char*)ft_strnew(rules->len_word);
	ft_memset(res, ' ', rules->len_word);
	ft_filldec_long(res, (unsigned long)(num * rules->sign), start, rules);
	ft_fillprec_long(&res, num * rules->sign -
	(unsigned long)(num * rules->sign), start, rules);
	return (res);
}

char							*ft_dtoa_long(long double num, t_rules *rules)
{
	long long					start;
	long long					fin;
	char						*res;
	uintmax_t					num_aux;
	t_dbl						dbl;

	dbl.dlong = num;
	rules->len_num = 1;
	rules->prec = rules->prec_on ? rules->prec : 6;
	rules->sign = dbl.t_dblp.sign ? -1 : 1;
	num_aux = num;
	num_aux = (unsigned long long)(num * rules->sign);
	while (num_aux /= 10)
		rules->len_num++;
	fin = pf_setstart_f(rules, &start);
	rules->len_word = (fin > rules->width ? fin : rules->width);
	res = (char*)ft_strnew(rules->len_word);
	ft_memset(res, ' ', rules->len_word);
	ft_filldec_long(res, (unsigned long)(num * rules->sign), start, rules);
	ft_fillprec_long(&res, num * rules->sign -
	(unsigned long)(num * rules->sign), start, rules);
	return (res);
}
