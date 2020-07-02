/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_worker_zjmp.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 16:05:04 by limry             #+#    #+#             */
/*   Updated: 2020/07/02 16:05:04 by limry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"

t_car		*op_zjmp(t_car *car, t_worker *wk, int ar_3t_3l[6])
{
	int		v[3];
	int		offset_flag[2];

	offset_flag[0] = 1;
	offset_flag[1] = 1;
	v[0] = vm_op_get_val(wk, car, ar_3t_3l, offset_flag) % IDX_MOD;
	if (!car->carry)
	{
		if (wk->flag_log & LOG_OP)
			ft_printfd(wk->io->cout, "P %d| zjump %d FAILED\n",
					car->id, v[0]);
		return (car);
	}
	if (wk->flag_log & LOG_OP || wk->gameid > 0)
		vm_op_log(car, v, ar_3t_3l, wk);
	car->position = vm_get_addr(car->position + v[0]);
	car->step_size = 0;
	return (car);
}
