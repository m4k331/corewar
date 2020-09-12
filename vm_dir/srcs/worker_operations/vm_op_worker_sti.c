/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_worker_sti.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 16:05:17 by limry             #+#    #+#             */
/*   Updated: 2020/07/02 16:05:17 by limry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"

t_car		*op_sti(t_car *car, t_worker *wk, int ar_3t_3l[6])
{
	int		v[3];
	int		offset_flag[2];

	offset_flag[0] = 1 + 1;
	offset_flag[1] = 1;
	ft_bzero(v, 12);
	v[0] = vm_op_get_val(wk, car, ar_3t_3l, offset_flag);
	offset_flag[0] += ar_3t_3l[3];
	v[1] = vm_op_get_val(wk, car, ar_3t_3l + 1, offset_flag);
	offset_flag[0] += ar_3t_3l[4];
	v[2] = vm_op_get_val(wk, car, ar_3t_3l + 2, offset_flag);
	vm_op_from_int32_to_byte(wk->map, v[0],
			car->position + (v[1] + v[2]) % IDX_MOD, REG_SIZE);
	vm_op_set_val_to_byte(wk->set, -car->reg[0],
	car->position + (v[1] + v[2]) % IDX_MOD, REG_SIZE);
	if (wk->flag_log & LOG_OP || wk->gameid > 0)
	{
		vm_op_log(car, v, ar_3t_3l, wk);
		if (wk->flag_log & LOG_OP)
			ft_printfd(wk->io->cout, "   | -> store to %d + %d = %d (%d)\n",
				v[1], v[2], (v[1] + v[2]) % IDX_MOD,
				car->position + (v[1] + v[2]) % IDX_MOD);
	}
	return (car);
}
