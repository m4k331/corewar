/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_message_game_loaded_notify.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kona <kona@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 08:02:41 by kona              #+#    #+#             */
/*   Updated: 2020/04/10 08:02:41 by kona             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"

void	vm_message_game_loaded_notify(t_worker *wk)
{
	vm_message_set_header(TYPE_GAME_LOADED,
	wk->gameid, 4, wk->io->netbuf);
	darr_join(wk->io->netbuf, (uint8_t*)&wk->gameid, 4, sizeof(uint8_t));
	vm_socket_send_buff(wk->io);
}
