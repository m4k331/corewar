/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_proc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 17:07:20 by limry             #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char				*pf_proczero(t_rules *rules)
{
	char				*res;

	res = ft_strnew(0);
	rules->len_word = 0;
	return (res);
}

static void				pf_setstart_u(t_rules *rules, long long *start)
{
	long long			len_sign;
	long long			prec_width;

	len_sign = 0;
	prec_width = (rules->prec + len_sign) > rules->width ?
			(rules->prec + len_sign) : rules->width;
	if (!(rules->flags & 4UL))
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

static char				*pf_fillrest_u(char *res, t_rules *rules,
						long long strt)
{
	while (!rules->num && (!rules->prec_on || rules->prec) && strt)
	{
		res[--strt] = '0';
		if (rules->prec_on && rules->prec)
			rules->prec--;
		if (!(rules->flags & 2UL))
			break ;
	}
	while (((rules->prec_on && rules->prec > rules->width)
	|| (rules->prec <= rules->width)) && rules->prec > 0 && strt > 0)
	{
		res[--strt] = '0';
		rules->prec--;
	}
	while (strt && rules->num && rules->flags & 2UL && !rules->prec_on)
		res[--strt] = '0';
	return (res);
}

char					*ft_itoa_ulen(unsigned int n, t_rules *rules)
{
	char				*res;
	long long			strt;
	unsigned int		aux_num;

	aux_num = n;
	rules->num = (n != 0);
	while (aux_num /= 10)
		rules->len_num++;
	rules->sign = 1;
	pf_setstart_u(rules, &strt);
	rules->len_word = (rules->width > strt ? rules->width : strt);
	if (!n && !rules->width && rules->prec_on && !rules->prec)
		return (res = pf_proczero(rules));
	res = ft_strnew(rules->len_word);
	pf_prepstr(rules, res, strt);
	while (strt > 0 && n)
	{
		res[--strt] = '0' + (n % 10) * rules->sign;
		n /= 10;
		if (rules->prec_on)
			rules->prec--;
	}
	return (pf_fillrest_u(res, rules, strt));
}

char					*ft_itoa_ulong(unsigned long long n, t_rules *rules)
{
	char				*res;
	long long			strt;
	unsigned long long	aux_num;

	aux_num = n;
	rules->num = (n != 0);
	while (aux_num /= 10)
		rules->len_num++;
	rules->sign = 1;
	pf_setstart_u(rules, &strt);
	rules->len_word = (rules->width > strt ? rules->width : strt);
	if (!n && !rules->width && rules->prec_on && !rules->prec)
		return (res = pf_proczero(rules));
	res = ft_strnew(rules->len_word);
	pf_prepstr(rules, res, strt);
	while (strt > 0 && n)
	{
		res[--strt] = '0' + (n % 10) * rules->sign;
		n /= 10;
		if (rules->prec_on)
			rules->prec--;
	}
	return (pf_fillrest_u(res, rules, strt));
}
