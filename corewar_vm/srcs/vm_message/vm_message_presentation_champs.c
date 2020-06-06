/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_message_presentation_champs.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kona <kona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 21:53:00 by kona              #+#    #+#             */
/*   Updated: 2020/06/06 19:02:58 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"

void	vm_message_champs_present(t_worker *wk)
{

	vm_message_set_header(TYPE_CHAMP_PRES,
	wk->gameid, 4 + (int)wk->log->len_data, wk->io->netbuf);
	darr_join(wk->io->netbuf, (uint8_t*)wk->log->start, wk->log->len_data,
			sizeof(uint8_t));
	vm_socket_send_buff(wk->io);
}
