/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_message_endgame.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kona <kona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 08:02:49 by kona              #+#    #+#             */
/*   Updated: 2020/04/10 08:02:49 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"

void		vm_message_endgame(t_worker *wk)
{
	int		ll;

	ll = -wk->last_lived;
	vm_message_set_header(TYPE_GAME_END,
	wk->gameid, 0, wk->io->netbuf);
	darr_join(wk->io->netbuf,
	(uint8_t*)&(ll), 1, sizeof(uint8_t));
	darr_join(wk->io->netbuf,
	(uint8_t*)wk->log->start, wk->log->len_data, sizeof(uint8_t));
	vm_socket_int_to_bytes((uint8_t*)(wk->io->netbuf->start) + 5,
						wk->io->netbuf->len_data - 9, 4);
	vm_socket_send_buff(wk->io);
}
