/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_message_proc_statuses.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 16:01:41 by limry             #+#    #+#             */
/*   Updated: 2020/07/02 16:01:41 by limry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"

void		vm_message_proc_statuses(t_worker *wk)
{
	vm_message_set_header(TYPE_DEAD_PROC,
	wk->gameid, wk->log->len_data, wk->io->netbuf);
	darr_join(wk->io->netbuf,
	(uint8_t*)wk->log->start, wk->log->len_data, sizeof(uint8_t));
	vm_socket_send_buff(wk->io);
}
