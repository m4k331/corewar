/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_op_worker_live.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 16:06:25 by limry             #+#    #+#             */
/*   Updated: 2020/07/02 16:06:25 by limry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"

t_car		*op_live(t_car *car, t_worker *wk, int32_t args_3t_3l[6])
{
	int		id_player;

	wk->num_live++;
	car->last_live = wk->cur_ctd;
	id_player = vm_op_byte_to_32int(wk->map, vm_get_addr(car->position + 1),
			args_3t_3l[3]);
	if (id_player < 0 && id_player > -5 && &(wk->champs[id_player]) != NULL)
		wk->last_lived = id_player;
	if (wk->flag_log & LOG_OP)
		ft_printfd(wk->io->cout,
		"P %4d | live %d\n",
		car->id, id_player);
	if (id_player < 0 && id_player > -5 && wk->flag_log & LOG_LIVE
	&& wk->gameid > 0)
	{
		ft_printfs(wk->log, "Player %d (%s) is alive!\n",
				-id_player, wk->champs[-id_player - 1].name);
		if (wk->flag_log & LOG_LIVE)
			ft_putstr_fd(wk->log->start, wk->io->cout);
		if (wk->gameid > 0)
			vm_message_operation(wk, car);
		dstr_remove_front(wk->log, wk->log->len);
	}
	return (car);
}
