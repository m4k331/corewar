/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   16_vm_worker_aff.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kona <kona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 08:22:27 by kona              #+#    #+#             */
/*   Updated: 2020/06/05 14:43:34 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"

t_car		*op_aff(t_car *car, t_worker *wk, int ar_3t_3l[6])
{
	int		v[3];
	int		offset_flag[2];

	offset_flag[0] = 1 + 1;
	offset_flag[1] = 0;
	v[0] = vm_op_byte_to_32int(wk->map,
		car->position + offset_flag[0], ar_3t_3l[3]);
	ft_putchar_fd((char)car->reg[v[0]], wk->io->cout);
	if (wk->flag_log & LOG_OP || wk->gameid > 0)
		vm_op_log(car, v, ar_3t_3l, wk);
	return (car);
}
