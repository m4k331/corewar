/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darr_remove_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 15:55:11 by limry             #+#    #+#             */
/*   Updated: 2020/06/06 19:02:59 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_darr.h"

void			darr_remove_back(t_darr *darr, int64_t l)
{
	if (l <= darr->len_data)
	{
		darr->len_data -= l;
		darr->len -= l;
		return ;
	}
	darr->len = 0;
	darr->start = darr->data;
	darr->len_data = 0;
}
