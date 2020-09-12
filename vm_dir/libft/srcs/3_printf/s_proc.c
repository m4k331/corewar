/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_proc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 23:18:13 by limry             #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int			ft_proc_null(t_rules *rules, char **res)
{
	s_writer("(null)", rules, res, 0);
	return (1);
}

static void			pf_fill(t_rules *rules, char *res, char *arg, int f_mod)
{
	if (rules->flags & 4)
		ft_memmove(res, arg, rules->len_num);
	else
	{
		if (rules->prec_on)
			ft_memmove(res + (rules->len_word - rules->len_num),
					arg, rules->len_num);
		else
			ft_memmove(res + (rules->len_word - rules->len_num),
					arg, rules->len_num);
	}
	if (rules->flags & 2 && !f_mod)
		ft_memset(res, '0', (rules->len_word - rules->len_num));
}

static void			pf_setstart_s(t_rules *rules, long long *start)
{
	if (rules->prec_on)
	{
		if (rules->len_num > rules->prec)
			*start = rules->prec;
		else
			*start = rules->len_num;
	}
	else
		*start = rules->len_num;
}

static int			pf_scheckexp(t_rules *rules, char *arg, char **res)
{
	if (!arg)
		return (ft_proc_null(rules, res));
	if (*arg == '\0' && rules->width == 0)
	{
		rules->len_word = 0;
		return (1);
	}
	return (0);
}

void				s_writer(char *arg, t_rules *rules, char **res, int f_mod)
{
	long long		start;

	if (pf_scheckexp(rules, arg, res))
		return ;
	rules->len_num = ft_strlen(arg);
	pf_setstart_s(rules, &start);
	rules->len_word = rules->width > start ? rules->width : start;
	*res = ft_strnew(rules->len_word);
	ft_memset(*res, ' ', rules->len_word);
	rules->len_num = (rules->prec_on && rules->prec < rules->len_num) ?
			rules->prec : rules->len_num;
	pf_fill(rules, *res, arg, f_mod);
}
