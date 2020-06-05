/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   13_vm_worker_lld.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kona <kona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 08:21:49 by kona              #+#    #+#             */
/*   Updated: 2020/06/05 14:43:34 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"

t_car		*op_lld(t_car *car, t_worker *wk, int32_t ar_3t_3l[6])
{
	int		offset_flag[2];
	int		v[3];

	offset_flag[0] = 1 + 1;
	offset_flag[1] = 0;
	v[0] = vm_op_get_val(wk, car, ar_3t_3l, offset_flag);
	offset_flag[0] += ar_3t_3l[3];
	v[1] = vm_op_byte_to_32int(wk->map,
		car->position + offset_flag[0], ar_3t_3l[4]);
	car->reg[v[1] - 1] = v[0];
	car->carry = v[0] ? 0 : 1;
	if (wk->flag_log & LOG_OP || wk->gameid > 0)
		vm_op_log(car, v, ar_3t_3l, wk);
	return (car);
}
