/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_stringrunner.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kona <kona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 09:42:40 by kona              #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		pf_printtail(int fd, const char *format,
				char *print_point, int *chars_printed)
{
	if (format != print_point)
	{
		if (0 <= write(fd, print_point, format - print_point))
		{
			*chars_printed += format - print_point;
			return (1);
		}
		else
			return (-1);
	}
	return (1);
}

static int		pf_printtail_s(t_dstr *dstr, const char *format,
				char *print_point, int *chars_printed)
{
	if (format != print_point)
	{
		dstr_joinstr_len(dstr, print_point, format - print_point);
		*chars_printed += (int)(format - print_point);
		return (1);
	}
	return (1);
}

int				pf_stringrunner(int fd, const char *format, va_list *arg)
{
	char		*print_point;
	t_rules		rules;
	int			chars_printed;

	rules.skip = 0;
	rules.fd = fd;
	chars_printed = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format = ft_parse(++format, arg, &rules);
			if (rules.err)
				return (-1);
			chars_printed += rules.len_word;
		}
		print_point = rules.skip ? rules.word_start : (char *)format;
		pf_skip_non_prc(&rules, &format);
		if (0 > pf_printtail(fd, format, print_point, &chars_printed))
			return (-1);
	}
	return (chars_printed);
}

int				pf_stringrunner_s(t_dstr *dstr, const char *format,
				va_list *arg)
{
	char		*print_point;
	t_rules		rules;
	int			chars_printed;

	rules.skip = 0;
	rules.dstr = dstr;
	chars_printed = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format = ft_parse_s(++format, arg, &rules);
			if (rules.err)
				return (-1);
			chars_printed += rules.len_word;
		}
		print_point = rules.skip ? rules.word_start : (char *)format;
		pf_skip_non_prc(&rules, &format);
		if (0 > pf_printtail_s(dstr, format, print_point, &chars_printed))
			return (-1);
	}
	return (chars_printed);
}
