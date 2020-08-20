/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_proc_prec_Proc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 17:13:53 by limry             #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	pf_setstart_f(t_rules *rules, long long *start)
{
	long long	len_sign;
	long long	len_dot;

	len_sign = ((rules->sign < 0) || rules->flags & 16 || rules->flags & 8);
	len_dot = (rules->prec || rules->flags & 1);
	if (!(rules->flags & 4))
	{
		if (rules->len_num + rules->prec + len_sign + len_dot > rules->width)
		{
			*start = len_sign;
			return (rules->len_num + rules->prec + len_sign + len_dot);
		}
		else
		{
			*start = rules->width - (rules->prec + len_dot + rules->len_num);
			return (rules->width);
		}
	}
	else
	{
		*start = len_sign;
		return (rules->len_num + rules->prec + len_sign + len_dot);
	}
}

static char		*fill_numbers(t_rules *rules, char *digits,
				long long start)
{
	char		*res;
	t_u8		if_point;

	res = ft_strnew(rules->len_word);
	ft_memset(res, ' ', rules->len_word);
	if_point = (rules->prec || rules->flags & 1UL);
	ft_strncpy(res + start, digits, rules->len_num);
	if (if_point)
		res[start + rules->len_num] = '.';
	if (rules->prec)
		ft_strncpy(res + start + rules->len_num + if_point,
			digits + rules->len_num, (rules->prec));
	if (rules->flags & 2UL)
		ft_memset(res, '0', start);
	if (rules->sign < 0 || rules->flags & 16UL)
		res[(start - 1) * !(rules->flags & 2UL)] = rules->sign < 0 ? '-' : '+';
	else if (rules->flags & 8UL)
		res[(start - 1) * !(rules->flags & 2UL)] = ' ';
	ft_memset(res + start + rules->len_num + if_point + rules->prec, ' ',
			rules->len_word -
			(start + rules->len_num + if_point + rules->prec));
	return (res);
}

char			*handle_prec(char *digits, t_rules *rules, int exp)
{
	long long	fin;
	long long	start;
	char		*res;
	char		*aux;

	rules->prec = rules->prec_on ? rules->prec : 6;
	rules->len_num = exp <= 0 ? 1 : exp;
	fin = pf_setstart_f(rules, &start);
	rules->len_word = (fin > rules->width ? fin : rules->width);
	digits = pf_dbl_rounding(digits, rules, &exp, &start);
	aux = ft_strnew(rules->prec + rules->len_num);
	ft_memset(aux, '0', rules->prec + rules->len_num);
	res = digits;
	digits = ft_strjoin(digits, aux);
	free(aux);
	free(res);
	res = fill_numbers(rules, digits, start);
	free(digits);
	return (res);
}
