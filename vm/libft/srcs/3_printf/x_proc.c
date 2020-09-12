/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xX_proc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 16:16:13 by limry             #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t		pf_setstart_x(t_rules *rules, int num_zero)
{
	long long		len_sign;
	long long		prec_width;

	len_sign = (rules->sign < 0 || rules->flags & 1) * 2 * num_zero;
	prec_width = (rules->prec + len_sign) > rules->width ?
			(rules->prec + len_sign) : rules->width;
	if (!(rules->flags & 4))
	{
		if ((rules->len_num + len_sign) < prec_width)
			return (prec_width);
		else
			return (rules->len_num + len_sign);
	}
	else
	{
		if (rules->prec_on)
		{
			if (rules->len_num < rules->prec)
				return (rules->prec + len_sign);
			else
				return (rules->len_num + len_sign);
		}
		else
			return (rules->len_num + len_sign);
	}
}

static void			pf_preparestr_x(long long *start, t_rules *rules,
					char **res, int num)
{
	*start = pf_setstart_x(rules, num);
	rules->len_word = (*start > rules->width ? *start : rules->width);
	*res = ft_strnew(rules->len_word);
	ft_memset(*res, ' ', rules->len_word);
	if (*start >= rules->width)
		ft_memset(res, '0', rules->len_word - *start);
}

char				*itoa_base_len(unsigned int num, int base,
					int letter, t_rules *rules)
{
	unsigned int	aux_num;
	char			chars[17];
	char			*res;
	long long		start;

	ft_strncpy(chars, (letter < 96 ? "0123456789ABCDEF" :
	"0123456789abcdef"), 16);
	aux_num = num;
	rules->num = (num != 0);
	rules->sign = 1;
	while (aux_num /= base)
		rules->len_num++;
	if (rules->prec_on && !rules->prec && !num)
		return (pf_zero_case_x(rules));
	pf_preparestr_x(&start, rules, &res, num != 0);
	while (start > 0 && num)
	{
		res[--start] = chars[num % base];
		num /= base;
		if (rules->prec_on && rules->prec)
			rules->prec--;
	}
	(rules->prec_on && rules->prec) ? pf_fillprec_x(rules, res, start, letter) :
		pf_fillnoprec_x(rules, res, start, letter);
	return (res);
}

char				*itoa_base_long(unsigned long num, int base,
					int letter, t_rules *rules)
{
	unsigned long	aux_num;
	char			chars[17];
	long long		start;
	char			*res;

	ft_strncpy(chars, (letter < 96 ? "0123456789ABCDEF" :
	"0123456789abcdef"), 16);
	aux_num = num;
	rules->num = (num != 0);
	rules->sign = 1;
	while (aux_num /= base)
		rules->len_num++;
	if (rules->prec_on && !rules->prec && !num)
		return (pf_zero_case_x(rules));
	pf_preparestr_x(&start, rules, &res, num != 0);
	while (start > 0 && num)
	{
		res[--start] = chars[num % base];
		num /= base;
		if (rules->prec_on && rules->prec)
			rules->prec--;
	}
	(rules->prec_on && rules->prec) ? pf_fillprec_x(rules, res, start, letter) :
	pf_fillnoprec_x(rules, res, start, letter);
	return (res);
}

char				*itoa_base_short(unsigned short num, int base,
					int letter, t_rules *rules)
{
	unsigned short	aux_num;
	char			chars[17];
	long long		start;
	char			*res;

	ft_strncpy(chars, (letter < 96 ? "0123456789ABCDEF" :
	"0123456789abcdef"), 16);
	aux_num = num;
	rules->num = (num != 0);
	rules->sign = 1;
	while (aux_num /= base)
		rules->len_num++;
	if (rules->prec_on && !rules->prec && !num)
		return (pf_zero_case_x(rules));
	pf_preparestr_x(&start, rules, &res, num != 0);
	while (start > 0 && num)
	{
		res[--start] = chars[num % base];
		num /= base;
		if (rules->prec_on && rules->prec)
			rules->prec--;
	}
	(rules->prec_on && rules->prec) ? pf_fillprec_x(rules, res, start, letter) :
	pf_fillnoprec_x(rules, res, start, letter);
	return (res);
}
