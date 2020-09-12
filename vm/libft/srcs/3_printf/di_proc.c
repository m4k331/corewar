/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   di_proc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 16:03:53 by limry             #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void			pf_setstart_di(t_rules *rules, long long *start)
{
	long long		len_sign;
	long long		prec_width;

	len_sign = (rules->sign < 0 || rules->flags & 16 || rules->flags & 8);
	prec_width = (rules->prec + len_sign) > rules->width ?
			(rules->prec + len_sign) : rules->width;
	if (!(rules->flags & 4))
	{
		if ((rules->len_num + len_sign) < prec_width)
			*start = prec_width;
		else
			*start = rules->len_num + len_sign;
	}
	else
	{
		if (rules->prec_on)
		{
			if (rules->len_num < rules->prec)
				*start = rules->prec + len_sign;
			else
				*start = rules->len_num + len_sign;
		}
		else
			*start = rules->len_num + len_sign;
	}
}

static void			pf_fillstr(char *res, t_rules *rules, long long strt)
{
	while (!rules->num && (!rules->prec_on || rules->prec) && strt)
	{
		res[--strt] = '0';
		if (rules->prec_on && rules->prec)
			rules->prec--;
		if (!(rules->flags & 2))
			break ;
	}
	while (((rules->prec_on && rules->prec > rules->width)
	|| (rules->prec <= rules->width)) && rules->prec > 0 && strt > 0)
	{
		res[--strt] = '0';
		rules->prec--;
	}
	while (strt && rules->num && rules->flags & 2 && !rules->prec_on)
		res[--strt] = '0';
	if ((rules->flags & 8) && !(rules->flags & 16))
		res[(!strt || (!rules->num && rules->prec) || rules->flags & 4)
			? 0 : strt - 1] = rules->sign == -1 ? '-' : ' ';
	else if ((rules->flags & 16) || rules->sign == -1)
		res[(!strt || (!rules->num && rules->prec) || rules->flags & 4)
		? 0 : strt - 1] = rules->sign == -1 ? '-' : '+';
}

char				*ft_itoa_len(int n, t_rules *rules)
{
	char			*res;
	long long		strt;
	int				aux_num;

	aux_num = n;
	rules->num = (n != 0);
	while (aux_num /= 10)
		rules->len_num++;
	rules->sign = n < 0 ? -1 : 1;
	if (!n && rules->prec_on)
		rules->len_num--;
	pf_setstart_di(rules, &strt);
	rules->len_word = (rules->width > strt ? rules->width : strt);
	res = ft_strnew(rules->len_word);
	pf_prepstr(rules, res, strt);
	while (strt > 0 && (n))
	{
		res[--strt] = '0' + (n % 10) * rules->sign;
		n /= 10;
		if (rules->prec_on)
			rules->prec--;
	}
	pf_fillstr(res, rules, strt);
	return (res);
}

char				*ft_itoa_long(long long n, t_rules *rules)
{
	char			*res;
	long long		strt;
	long long		aux_num;

	aux_num = n;
	rules->num = (n != 0);
	while (aux_num /= 10)
		rules->len_num++;
	rules->sign = n < 0 ? -1 : 1;
	if (!n && rules->prec_on)
		rules->len_num--;
	pf_setstart_di(rules, &strt);
	rules->len_word = (rules->width > strt ? rules->width : strt);
	res = ft_strnew(rules->len_word);
	pf_prepstr(rules, res, strt);
	while (strt > 0 && (n || rules->prec > rules->width))
	{
		res[--strt] = '0' + (n % 10) * rules->sign;
		n /= 10;
		if (rules->prec_on)
			rules->prec--;
	}
	pf_fillstr(res, rules, strt);
	return (res);
}
