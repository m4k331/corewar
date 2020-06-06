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

static void			pf_fillrules(t_rules *rules, char **res,
					long long full_len, int arg)
{
	if (rules->flags & 4UL)
		(*res)[0] = arg;
	else
		(*res)[full_len - 1] = arg;
}

static void			prepare_str(t_rules *rules, char **res)
{
	*res = ft_strnew(rules->len_word);
	ft_memset(*res, ' ', rules->len_word);
}

void				c_writer(int arg, t_rules *rules, char **res)
{
	rules->len_word = rules->width ? rules->width : 1;
	prepare_str(rules, res);
	pf_fillrules(rules, res, rules->len_word, arg);
}
