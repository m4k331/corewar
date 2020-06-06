/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_vm_worker_add.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kona <kona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 08:20:11 by kona              #+#    #+#             */
/*   Updated: 2020/06/06 19:02:58 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"

t_car		*op_add(t_car *car, t_worker *wk, int ar_3t_3l[6])
{
	int		v[3];
	int		offset;

	offset = 1 + 1;
	v[0] = vm_op_byte_to_32int(wk->map, car->position + offset, ar_3t_3l[3]);
	offset += ar_3t_3l[3];
	v[1] = vm_op_byte_to_32int(wk->map, car->position + offset, ar_3t_3l[4]);
	offset += ar_3t_3l[4];
	v[2] = vm_op_byte_to_32int(wk->map, car->position + offset, ar_3t_3l[5]);
	car->reg[v[2] - 1] = car->reg[v[0] - 1] + car->reg[v[1] - 1];
	car->carry = car->reg[v[2] - 1] ? 0 : 1;
	if (wk->flag_log & LOG_OP || wk->gameid > 0)
		vm_op_log(car, v, ar_3t_3l, wk);
	return (car);
}
