/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_message_presentation_champs.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 16:01:46 by limry             #+#    #+#             */
/*   Updated: 2020/07/04 17:32:53 by limry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"

void	vm_message_champs_present(t_worker *wk)
{
	vm_message_set_header(TYPE_CHAMP_PRES,
	wk->gameid, (int)wk->log->len_data, wk->io->netbuf);
	darr_join(wk->io->netbuf, (uint8_t*)wk->log->start, wk->log->len_data,
			sizeof(uint8_t));
	vm_socket_send_buff(wk->io);
}
