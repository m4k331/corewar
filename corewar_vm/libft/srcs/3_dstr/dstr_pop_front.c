/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dstr_pop_front.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kona <kona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 09:41:37 by kona              #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dstr.h"

char			*dstr_pop_front(t_dstr *dstr, char **res, uint64_t l)
{
	if (l <= dstr->len_data)
	{
		if (res)
			*res = ft_strsub(dstr->start, 0, l);
		dstr->start += l;
		dstr->len_data -= l;
		if (res)
			return (*res);
		else
			return (NULL);
	}
	*res = ft_strsub(dstr->start, 0, dstr->len_data);
	ft_bzero(dstr->data, dstr->cap);
	dstr->len = 0;
	dstr->start = dstr->data;
	dstr->len_data = 0;
	return (*res);
}
