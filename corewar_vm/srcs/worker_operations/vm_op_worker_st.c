/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_vm_worker_st.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kona <kona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 08:19:49 by kona              #+#    #+#             */
/*   Updated: 2020/06/06 19:02:58 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"

t_car		*op_st(t_car *car, t_worker *wk, int ar_3t_3l[6])
{
	int		v[3];
	int		offset;

	offset = 1 + 1;
	v[0] = vm_op_byte_to_32int(wk->map, vm_get_addr(car->position + offset),
			ar_3t_3l[3]);
	offset += ar_3t_3l[3];
	v[1] = vm_op_byte_to_32int(wk->map, vm_get_addr(car->position + offset),
			ar_3t_3l[4]);
	if (ar_3t_3l[1] == T_REG)
		car->reg[v[1] - 1] = car->reg[v[0] - 1];
	else if (ar_3t_3l[1] == T_IND)
	{
		vm_op_from_int32_to_byte(wk->map, car->reg[v[0] - 1],
		vm_get_addr(car->position + v[1] % IDX_MOD), REG_SIZE);
		vm_op_set_val_to_byte(wk->set, -car->reg[0],
				car->position + v[1] % IDX_MOD, REG_SIZE);
	}
	if (wk->flag_log & LOG_OP || wk->gameid > 0)
		vm_op_log(car, v, ar_3t_3l, wk);
	return (car);
}
