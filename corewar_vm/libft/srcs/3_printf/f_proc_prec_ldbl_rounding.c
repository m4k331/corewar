/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_proc_prec_ldbl_rounding.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 17:24:41 by limry             #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		check_tail(long long len, char *tail)
{
	while (tail[len++])
		if (tail[len] && tail[len] != '0')
			return (1);
	return (0);
}

static char		*trim_head_zeroes(char **digits)
{
	char		*res;
	size_t		res_start;
	size_t		digits_len;

	res_start = 0;
	digits_len = ft_strlen(*digits);
	while ((*digits)[res_start] == '0')
		res_start++;
	res = ft_strnew(digits_len - res_start);
	res = ft_memcpy(res, *digits + res_start, digits_len - res_start);
	free(*digits);
	return (res);
}

static char		*add_left_zeroes(char *digits, int *exp, long long *len)
{
	char		*aux;
	char		*to_del;

	if (*exp <= 0)
	{
		*exp = *exp - 1;
		aux = ft_strnew(-*exp * sizeof(char));
		ft_memset(aux, '0', -*exp * sizeof(char));
		to_del = digits;
		digits = ft_strjoin(aux, digits);
		*len = *len - *exp;
		free(aux);
		free(to_del);
	}
	return (digits);
}

static char		*add_right_zeroes(char *digits, int exp, long long *len)
{
	char		*to_del;

	if (exp > 0)
	{
		to_del = digits;
		digits = ft_strjoin("0", digits);
		free(to_del);
		*len = *len + 1;
	}
	return (digits);
}

char			*pf_dbl_rounding(char *digits, t_rules *rules,
				int *exp, long long *start)
{
	long long	len;

	len = *exp + rules->prec;
	digits = add_left_zeroes(digits, exp, &len);
	if (digits[len] < '5' || (digits[len] == '5' &&
	digits[len - 1] % 2 == 0 && !check_tail(len, digits)))
		return (digits);
	digits = add_right_zeroes(digits, *exp, &len);
	while (digits[--len] == '9')
		digits[len] = '0';
	if (*exp > 0 && !len && digits[len] == '0')
	{
		rules->len_num += 1;
		if (*start)
			*start = *start - 1;
		else if (*exp > 0)
			rules->len_word++;
	}
	digits[len] += 1;
	if (*exp > 0)
		digits = trim_head_zeroes(&digits);
	return (digits);
}
