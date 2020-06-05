/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   15_vm_worker_lfork.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kona <kona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 08:22:22 by kona              #+#    #+#             */
/*   Updated: 2020/06/05 14:43:34 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"

t_car			*op_lfork(t_car *car, t_worker *wk, int ar_3t_3l[6])
{
	int			v[3];
	int			offset_flag[2];

	offset_flag[0] = 1;
	offset_flag[1] = 1;
	v[0] = vm_op_get_val(wk, car, ar_3t_3l, offset_flag);
	if (wk->dead_head != -1)
		vm_fork_op_have_dead_head(wk, car, v, op_fork_set_pos_lfork);
	else
		car = vm_fork_op_nop_dead_head(wk, car, v, op_fork_set_pos_lfork);
	if (wk->flag_log & LOG_OP || wk->gameid > 0)
		vm_op_log(car, v, ar_3t_3l, wk);
	return (car);
}
