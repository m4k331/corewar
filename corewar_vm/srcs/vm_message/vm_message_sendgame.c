/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_message_sendgame.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 16:01:31 by limry             #+#    #+#             */
/*   Updated: 2020/07/02 16:01:31 by limry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"

void			vm_message_sendgame_carriages(t_worker *wk)
{
	t_car		*tmp;
	uint8_t		buf[4];

	tmp = (t_car*)wk->carrs + wk->live_head;
	while (tmp)
	{
		vm_socket_int_to_bytes(buf, tmp->id, 4);
		darr_join(wk->io->netbuf, buf, 4, sizeof(uint8_t));
		vm_socket_int_to_bytes(buf, tmp->position, 2);
		darr_join(wk->io->netbuf, buf, 2, sizeof(uint8_t));
		if (tmp->next == -1)
			break ;
		tmp = (t_car*)wk->carrs + tmp->next;
	}
}

void			vm_message_sendgame(t_worker *wk)
{
	uint8_t		buf[4];

	vm_message_set_header(TYPE_GAME_STAT,
	wk->gameid, 0, wk->io->netbuf);
	vm_socket_int_to_bytes(buf, wk->ctd, 4);
	darr_join(wk->io->netbuf, (uint8_t*)buf, 4, sizeof(uint8_t));
	vm_socket_int_to_bytes(buf, wk->cur_ctd, 4);
	darr_join(wk->io->netbuf, (uint8_t*)buf, 4, sizeof(uint8_t));
	vm_socket_int_to_bytes(buf, wk->num_live, 4);
	darr_join(wk->io->netbuf, (uint8_t*)buf, 4, sizeof(uint8_t));
	vm_socket_int_to_bytes(buf, wk->num_checks, 4);
	darr_join(wk->io->netbuf, (uint8_t*)buf, 4, sizeof(uint8_t));
	vm_socket_int_to_bytes(buf, wk->last_lived, 4);
	darr_join(wk->io->netbuf, (uint8_t*)buf, 1, sizeof(uint8_t));
	darr_join(wk->io->netbuf,
			wk->map, MEM_SIZE, sizeof(uint8_t));
	darr_join(wk->io->netbuf,
			wk->set, MEM_SIZE, sizeof(uint8_t));
	vm_message_sendgame_carriages(wk);
	vm_socket_int_to_bytes((uint8_t*)(wk->io->netbuf->start) + 5,
			wk->io->netbuf->len_data - 9L, 4);
	vm_socket_send_buff(wk->io);
}
