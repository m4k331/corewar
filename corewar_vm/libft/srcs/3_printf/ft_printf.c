/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 21:30:39 by limry             #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			specifier_parser(const char *str, va_list *arg,
				t_rules *rules, char **num)
{
	if (*str == '%')
		percent_writer(rules, num);
	else if (*str == 's')
		s_writer((char*)va_arg(*arg, char*), rules, num, 0);
	else if (*str == 'c')
		c_writer((int)va_arg(*arg, int), rules, num);
	else if (*str == 'p')
		p_writer(va_arg(*arg, void*), rules, num);
	else if (*str == 'f')
		f_writer(rules, arg, num);
	else if (*str == 'd' || *str == 'i')
		di_writer(rules, arg, num);
	else if (*str == 'u')
		u_writer(rules, arg, num);
	else if (*str == 'o')
		o_writer(rules, arg, num);
	else if (*str == 'x' || *str == 'X')
		x_writer(str, rules, arg, num);
	else if (*str == '\0')
		rules->len_word = 0;
	else
	{
		rules->word_start = (char*)str;
		rules->skip = 1;
	}
}

int				ft_printf(const char *format, ...)
{
	long long	chars_printed;
	va_list		arg;

	va_start(arg, format);
	chars_printed = pf_stringrunner(1, format, &arg);
	va_end(arg);
	return (chars_printed);
}

int				ft_printfd(int fd, const char *format, ...)
{
	long long	chars_printed;
	va_list		arg;

	va_start(arg, format);
	chars_printed = pf_stringrunner(fd, format, &arg);
	va_end(arg);
	return (chars_printed);
}

int				ft_printfs(t_dstr *dstr, const char *format, ...)
{
	long long	chars_printed;
	va_list		arg;

	va_start(arg, format);
	chars_printed = pf_stringrunner_s(dstr, format, &arg);
	va_end(arg);
	return (chars_printed);
}
