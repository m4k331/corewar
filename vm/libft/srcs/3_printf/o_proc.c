/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_proc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 16:57:00 by limry             #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char							*otoa_base_len(unsigned int num, int base,
								int letter, t_rules *rules)
{
	unsigned int				aux_num;
	char						*chars;
	char						*res;
	long long					start;

	chars = "0123456789ABCDEF";
	rules->num = (num != 0);
	rules->sign = 1;
	aux_num = num;
	while (aux_num /= base)
		rules->len_num++;
	start = pf_setstart(rules, num != 0);
	rules->len_word = start > rules->width ? start : rules->width;
	if (rules->prec_on && !rules->prec && !num)
		return (pf_zero_case_o(rules));
	res = ft_strnew(rules->len_word);
	pf_prepstr(rules, res, start);
	while (start > 0 && num)
	{
		res[--start] = chars[num % 8];
		num /= 8;
		if (rules->prec_on && rules->prec)
			rules->prec--;
	}
	return (pf_fillrest(res, rules, start, letter));
}

char							*otoa_base_long(unsigned long num, int base,
								int letter, t_rules *rules)
{
	unsigned long				aux_num;
	char						*chars;
	char						*res;
	long long					start;

	chars = "0123456789ABCDEF";
	rules->num = (num != 0);
	rules->sign = 1;
	aux_num = num;
	while (aux_num /= base)
		rules->len_num++;
	start = pf_setstart(rules, num != 0);
	rules->len_word = start > rules->width ? start : rules->width;
	if (rules->prec_on && !rules->prec && !num)
		return (pf_zero_case_o(rules));
	res = ft_strnew(rules->len_word);
	pf_prepstr(rules, res, start);
	while (start > 0 && num)
	{
		res[--start] = chars[num % 8];
		num /= 8;
		if (rules->prec_on && rules->prec)
			rules->prec--;
	}
	return (pf_fillrest(res, rules, start, letter));
}

char							*otoa_base_llong(unsigned long long num,
								int base, int letter, t_rules *rules)
{
	unsigned long long			aux_num;
	char						*chars;
	char						*res;
	long long					start;

	chars = "0123456789ABCDEF";
	rules->num = (num != 0);
	rules->sign = 1;
	aux_num = num;
	while (aux_num /= base)
		rules->len_num++;
	start = pf_setstart(rules, num != 0);
	rules->len_word = start > rules->width ? start : rules->width;
	if (rules->prec_on && !rules->prec && !num)
		return (pf_zero_case_o(rules));
	res = ft_strnew(rules->len_word);
	pf_prepstr(rules, res, start);
	while (start > 0 && num)
	{
		res[--start] = chars[num % base];
		num /= base;
		if (rules->prec_on && rules->prec)
			rules->prec--;
	}
	return (pf_fillrest(res, rules, start, letter));
}

char							*otoa_base_short(unsigned short num, int base,
								int letter, t_rules *rules)
{
	unsigned short				aux_num;
	char						*chars;
	char						*res;
	long long					start;

	chars = "0123456789ABCDEF";
	rules->num = (num != 0);
	rules->sign = 1;
	aux_num = num;
	while (aux_num /= base)
		rules->len_num++;
	start = pf_setstart(rules, num != 0);
	rules->len_word = start > rules->width ? start : rules->width;
	if (rules->prec_on && !rules->prec && !num)
		return (pf_zero_case_o(rules));
	res = ft_strnew(rules->len_word);
	pf_prepstr(rules, res, start);
	while (start > 0 && num)
	{
		res[--start] = chars[num % base];
		num /= base;
		if (rules->prec_on && rules->prec)
			rules->prec--;
	}
	return (pf_fillrest(res, rules, start, letter));
}

char							*otoa_base_hshort(unsigned char num, int base,
								int letter, t_rules *rules)
{
	unsigned char				aux_num;
	char						*chars;
	char						*res;
	long long					start;

	chars = "0123456789ABCDEF";
	rules->num = (num != 0);
	rules->sign = 1;
	aux_num = num;
	while (aux_num /= base)
		rules->len_num++;
	start = pf_setstart(rules, num != 0);
	rules->len_word = start > rules->width ? start : rules->width;
	if (rules->prec_on && !rules->prec && !num)
		return (pf_zero_case_o(rules));
	res = ft_strnew(rules->len_word);
	pf_prepstr(rules, res, start);
	while (start > 0 && num)
	{
		res[--start] = chars[num % base];
		num /= base;
		if (rules->prec_on && rules->prec)
			rules->prec--;
	}
	return (pf_fillrest(res, rules, start, letter));
}
