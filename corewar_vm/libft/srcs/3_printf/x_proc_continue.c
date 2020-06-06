/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_proc_continue.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 15:38:37 by limry             #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char			*pf_zero_case_x(t_rules *rules)
{
	char		*res;

	res = ft_strnew(rules->width);
	ft_memset(res, ' ', rules->width);
	rules->len_word = rules->width;
	return (res);
}

void			pf_fillprec_x(t_rules *rules,
				char *res, long long strt, int letter)
{
	while (rules->prec)
	{
		res[--strt] = '0';
		rules->prec--;
	}
	if (rules->flags & 1 && rules->prec)
		res[--strt] = '0';
	if (rules->num && rules->flags & 1 && strt)
	{
		res[--strt] = letter;
		res[--strt] = '0';
	}
}

void			pf_fillnoprec_x(t_rules *rules, char *res,
				long long strt, int letter)
{
	if (!rules->num)
		res[--strt] = '0';
	while (rules->flags & 2 && strt - ((rules->flags & 1 && rules->num) ?
	2 : 0) && !rules->prec_on)
		res[--strt] = '0';
	if (rules->num && rules->flags & 1 && strt)
	{
		res[--strt] = letter;
		res[--strt] = '0';
	}
}
