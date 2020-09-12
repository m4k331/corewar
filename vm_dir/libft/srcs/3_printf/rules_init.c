/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseman.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 15:26:05 by limry             #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static const char	*parse_flags(const char *str, t_rules *rules)
{
	while (*str == '+' || *str == ' ' || *str == '-'
	|| *str == '0' || *str == '#')
	{
		if (*str == '+')
			rules->flags |= 16;
		else if (*str == ' ')
			rules->flags |= 8;
		else if (*str == '-')
			rules->flags |= 4;
		else if (*str == '0')
			rules->flags |= 2;
		else if (*str == '#')
			rules->flags |= 1;
		str++;
	}
	return (str);
}

static const char	*parse_length_modifier(const char *str, t_rules *rules)
{
	if (*str == 'h')
	{
		if (*(str + 1) == 'h')
			rules->mod |= 320;
		rules->mod |= 64;
	}
	else if (*str == 'l')
	{
		if (*(str + 1) == 'l')
			rules->mod |= 640;
		rules->mod |= 128;
	}
	else if (*str == 'L')
		rules->mod |= 32;
	if (rules->mod > 128)
		str++;
	if (rules->mod > 0)
		str++;
	return (str);
}

static const char	*parse_width_and_prec(const char *str, t_rules *rules)
{
	rules->width = ft_atoi(str);
	while (ft_isdigit(*str))
		str++;
	if (*str == '.')
	{
		rules->prec_on = 1;
		rules->prec = ft_atoi(++str);
	}
	else
		rules->prec = 0;
	while (ft_isdigit(*str) || *str == '.')
		str++;
	if (rules->prec < 0)
	{
		rules->prec = 0;
		rules->prec_on = 0;
	}
	if (rules->width < 0)
		rules->width = 0;
	return (str);
}

char				*pf_rulesinit(t_rules *rules, const char **str,
					va_list *arg)
{
	char			*res;

	res = NULL;
	rules->width = 0;
	rules->prec = 0;
	rules->prec_on = 0;
	rules->flags = 0;
	rules->len_word = 0;
	rules->mod = 0;
	rules->len_num = 1;
	rules->word_start = (char*)str;
	rules->skip = 0;
	rules->color = "";
	rules->err = 0;
	*str = ft_parsecolor(*str, rules);
	*str = parse_flags(*str, rules);
	*str = parse_width_and_prec(*str, rules);
	*str = parse_length_modifier(*str, rules);
	*str = parse_flags(*str, rules);
	specifier_parser(*str, arg, rules, &res);
	return (res);
}
