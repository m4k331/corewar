/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_f_extremums.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 10:05:18 by limry             #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int			ld_isnan(t_dbl d)
{
	return (d.l == 0x7FF8000000000000ll ||
	d.l == 0xFFF8000000000000ll);
}

static int			ld_isinf(t_dbl d)
{
	return (d.l == 0x7FF0000000000000ll ||
	d.l == 0xFFF0000000000000ll);
}

int					handle_extremums(long double dbl,
					char **res, t_rules *rules)
{
	char			*arg_str;
	t_dbl			flt;

	flt.d = dbl;
	if (ld_isnan(flt))
		arg_str = "nan";
	else if (ld_isinf(flt))
	{
		if (flt.t_parts.sign)
			arg_str = "-inf";
		else if (rules->flags & 16)
			arg_str = "+inf";
		else if (rules->flags & 8)
			arg_str = " inf";
		else
			arg_str = "inf";
	}
	else
		return (0);
	rules->len_num = ft_strlen(arg_str);
	rules->prec = rules->len_num;
	rules->len_word = rules->width > rules->len_num ?
			rules->width : rules->len_num;
	s_writer(arg_str, rules, res, 1);
	return (1);
}

int					f_handle_extremums(t_dbl dbl, t_rules *rules, char **res)
{
	char			*word;

	if (!((rules->mod & 32UL && dbl.t_dblp.exponent == 0x7FFF) ||
		(!(rules->mod & 32UL) && dbl.t_parts.exponent == 0x7FF)))
		return (0);
	if ((!dbl.t_dblp.mantisa && rules->mod & 32UL) ||
		(!dbl.t_parts.mantisa && !(rules->mod & 32UL)))
		if (rules->sign < 0)
			word = "-inf";
		else if (rules->flags & 16UL)
			word = "+inf";
		else if (rules->flags & 8UL)
			word = " inf";
		else
			word = "inf";
	else
		word = "nan";
	rules->len_num = ft_strlen(word);
	rules->prec = rules->len_num;
	rules->len_word = rules->width > rules->len_num ?
			rules->width : rules->len_num;
	s_writer(word, rules, res, 1);
	return (1);
}
