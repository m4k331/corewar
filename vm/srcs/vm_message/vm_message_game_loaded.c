/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_message_game_loaded.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: limry <limry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 16:01:55 by limry             #+#    #+#             */
/*   Updated: 2020/07/02 23:49:14 by limry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_server.h"

void		vm_message_game_loaded(t_worker *wk, t_input *input)
{
	int		port;
	uint8_t	buf[4];

	if (input->mode == OFFLINE)
		return ;
	port = ft_atoi(wk->io->port);
	vm_message_set_header(TYPE_GAME_LOADED, wk->gameid, 4, input->io->netbuf);
	ft_bzero(&buf, 4);
	vm_socket_int_to_bytes(buf, port, 4);
	darr_join(input->io->netbuf, (uint8_t*)buf, 4, sizeof(uint8_t));
	vm_socket_send_buff(input->io);
}
