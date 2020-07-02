/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_message_operation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 16:01:50 by limry             #+#    #+#             */
/*   Updated: 2020/07/02 16:01:50 by limry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"

void		vm_message_operation(t_worker *wk, t_car *car)
{
	uint8_t	buf[4];

	vm_message_set_header(TYPE_OPERATION,
	wk->gameid, 0, wk->io->netbuf);
	vm_socket_int_to_bytes(buf, car->id, 4);
	darr_join(wk->io->netbuf,
			(uint8_t*)buf, 4, sizeof(uint8_t));
	vm_socket_int_to_bytes(buf, car->position, 2);
	darr_join(wk->io->netbuf,
			(uint8_t*)buf, 2, sizeof(uint8_t));
	darr_join(wk->io->netbuf,
			(uint8_t*)wk->log->start, wk->log->len_data, sizeof(uint8_t));
	vm_socket_int_to_bytes((uint8_t*)(wk->io->netbuf->start) + 5,
						wk->io->netbuf->len_data - 9, 4);
	vm_socket_send_buff(wk->io);
}
