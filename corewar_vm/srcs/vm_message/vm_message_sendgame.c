/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_message_sendgame.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kona <kona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 08:02:08 by kona              #+#    #+#             */
/*   Updated: 2020/06/05 14:43:34 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"

void			vm_message_sendgame_carriages(t_worker *wk)
{
	t_car		*tmp;

	tmp = (t_car*)wk->carrs + wk->live_head;
	while (tmp)
	{
		darr_join(wk->io->netbuf,
				(uint8_t*)&(tmp->id), 4, sizeof(uint8_t));
		darr_join(wk->io->netbuf,
				(uint8_t*)&(tmp->position), 2, sizeof(uint8_t));
		if (tmp->next == -1)
			break ;
		tmp = (t_car*)wk->carrs + tmp->next;
	}
}

void			vm_message_sendgame(t_worker *wk)
{
	vm_message_set_header(TYPE_GAME_STAT,
	wk->gameid, 0, wk->io->netbuf);
	darr_join(wk->io->netbuf, (uint8_t*)&(wk->ctd), 4, sizeof(uint8_t));
	darr_join(wk->io->netbuf,
			(uint8_t*)&(wk->cur_ctd), 4, sizeof(uint8_t));
	darr_join(wk->io->netbuf,
			(uint8_t*)&(wk->num_live), 4, sizeof(uint8_t));
	darr_join(wk->io->netbuf,
			(uint8_t*)&(wk->num_checks), 4, sizeof(uint8_t));
	darr_join(wk->io->netbuf,
			(uint8_t*)&(wk->last_lived), 1, sizeof(uint8_t));
	darr_join(wk->io->netbuf,
			wk->map, MEM_SIZE, sizeof(uint8_t));
	darr_join(wk->io->netbuf,
			wk->set, MEM_SIZE, sizeof(uint8_t));
	vm_message_sendgame_carriages(wk);
	vm_socket_int_to_bytes((uint8_t*)(wk->io->netbuf->start) + 5,
						wk->io->netbuf->len_data - 9, 4);
	vm_socket_send_buff(wk->io);
}
