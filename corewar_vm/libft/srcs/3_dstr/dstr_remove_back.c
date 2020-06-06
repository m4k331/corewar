/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dstr2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 19:30:03 by limry             #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dstr.h"

void			dstr_remove_back(t_dstr *dstr, uint64_t l)
{
	if (l < dstr->len_data)
	{
		dstr->len_data -= l;
		dstr->start[dstr->len_data] = '\0';
		dstr->len -= l;
		return ;
	}
	dstr->len = 0;
	dstr->start = dstr->data;
	dstr->start[0] = '\0';
	dstr->len_data = 0;
}
