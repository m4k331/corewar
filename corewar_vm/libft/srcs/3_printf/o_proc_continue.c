/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_proc_continue.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 15:29:15 by limry             #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char					*pf_zero_case_o(t_rules *rules)
{
	char				*res;
	long long			len;

	len = rules->width > 1 ? rules->width : 1;
	if (rules->flags & 1UL)
	{
		res = ft_strnew(len);
		ft_memset(res, ' ', len);
		rules->len_word = len;
	}
	else
	{
		res = ft_strnew(rules->width);
		ft_memset(res, ' ', rules->width);
		rules->len_word = rules->width;
	}
	if (rules->flags & 1UL)
	{
		if (rules->flags & 4UL)
			res[0] = '0';
		else
			res[len - 1] = '0';
	}
	return (res);
}

size_t					pf_setstart(t_rules *rules, int num_zero)
{
	long long			len_sign;
	long long			prec_width;

	len_sign = (rules->sign < 0 || rules->flags & 1UL) * num_zero;
	prec_width = rules->prec > rules->width ?
			rules->prec : rules->width;
	if (!(rules->flags & 4UL))
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
				return (rules->prec);
			else
				return (rules->len_num + len_sign);
		}
		else
			return (rules->len_num + len_sign);
	}
}

char					*pf_fillrest(char *res, t_rules *rules,
						long long strt, int letter)
{
	if (rules->prec_on && rules->prec)
	{
		while (rules->prec)
		{
			res[--strt] = '0';
			rules->prec--;
		}
		if (rules->flags & 1UL && rules->prec)
			res[--strt] = letter;
	}
	else
	{
		if (!rules->num || (rules->flags & 1UL && strt))
			res[--strt] = letter;
		while (rules->flags & 2UL && strt && !rules->prec_on)
		{
			res[--strt] = '0';
		}
	}
	return (res);
}
