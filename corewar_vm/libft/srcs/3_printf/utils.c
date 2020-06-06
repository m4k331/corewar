/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 15:33:04 by limry             #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void						pf_prepstr(t_rules *rules, char *res,
							long long start)
{
	ft_memset(res, ' ', rules->len_word);
	if (start < rules->width)
		ft_memset(res + start, ' ', rules->width - start);
	else
		ft_memset(res, '0', rules->len_word - start);
}

void						pf_procninenine(char **res_old, long long i,
							t_rules *rules, long long prec)
{
	char					*res;
	long long				ofst;

	rules->len_num++;
	ofst = 0;
	rules->len_num + prec >= rules->len_word ? rules->len_word++ : (ofst = 1);
	res = ft_strnew(rules->len_word);
	ft_memset(res, '0', rules->len_word);
	if (i)
		ft_memset(res, ' ', i - 1);
	if (rules->len_word > rules->len_word - prec)
		res[rules->len_word - prec - 1] = '.';
	if (rules->sign < 0 || rules->flags & 16 || rules->flags & 8)
	{
		res[i - 1 - ofst] = (*res_old)[rules->len_word -
					(rules->len_num + prec)];
		res[i - ofst] = '1';
	}
	else
		res[i - ofst] = '1';
	free(*res_old);
	*res_old = ft_strdup(res);
	free(res);
}

void						pf_rounding(char **res, long long i,
							t_rules *rules, long long prec)
{
	long long				end_num;

	if (rules->flags & 1 || prec)
		end_num = rules->len_word - rules->len_num - prec - 1;
	else
		end_num = rules->len_word - rules->len_num - prec;
	if ((*res)[i] == '.')
		i--;
	while ((*res)[i] == '9')
	{
		(*res)[i] = '0';
		if (i == end_num)
		{
			pf_procninenine(res, i, rules, prec);
			return ;
		}
		if ((*res)[--i] == '.')
			i--;
	}
	(*res)[i] += 1;
}

void						percent_writer(t_rules *rules,
							char **res)
{
	rules->len_word = rules->width > 1 ? rules->width : 1;
	if (!(*res = ft_strnew(rules->len_word)))
		return ;
	ft_memset(*res, ' ', rules->len_word);
	if ((rules->flags & 4))
		(*res)[0] = '%';
	else if (rules->flags & 2)
	{
		ft_memset(*res, '0', rules->len_word);
		(*res)[rules->len_word - 1] = '%';
	}
	else
		(*res)[rules->len_word - 1] = '%';
}

void						pf_skip_non_prc(t_rules *rules,
							const char **format)
{
	while ((**format != '%' || rules->skip) && **format)
	{
		(*format)++;
		rules->skip = 0;
	}
}
