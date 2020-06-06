/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bint_api.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 16:46:42 by limry             #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_bint		*bint_copy(t_bint *dst, const t_bint *src)
{
	size_t	len_new;

	if (!src)
		return (0);
	len_new = src->len;
	while (len_new--)
		dst->arr[len_new] = src->arr[len_new];
	dst->len = src->len;
	return (dst);
}

int			bint_comp(const t_bint *first, const t_bint *second)
{
	size_t	len;

	len = first->len;
	if (first->len > second->len)
		return (1);
	else if (first->len < second->len)
		return (-1);
	else
		while (len--)
		{
			if (first->arr[len] > second->arr[len])
				return (1);
			else if (first->arr[len] < second->arr[len])
				return (-1);
		}
	return (0);
}

size_t		bint_len(t_bint *bint)
{
	size_t	k;

	k = DBL_MAX_LEN;
	while (k--)
		if (bint->arr[k])
			return (1 + k);
	return (0);
}

void		get_exp_first_digit(t_dbl dbl, int *exp, t_rules *rules)
{
	if (rules->mod & 32ULL)
		*exp = get_exponent(dbl.dlong);
	else
		*exp = get_exponent(dbl.d);
}
