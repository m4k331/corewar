/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dstr_remove_front.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kona <kona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 09:41:45 by kona              #+#    #+#             */
/*   Updated: 2020/04/10 09:41:45 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dstr.h"

void			dstr_remove_front(t_dstr *dstr, uint64_t l)
{
	if (l < dstr->len_data)
	{
		dstr->len_data -= l;
		dstr->start += l;
		dstr->start[dstr->len_data] = '\0';
		return ;
	}
	dstr->len = 0;
	dstr->start = dstr->data;
	dstr->start[0] = '\0';
	dstr->len_data = 0;
}
